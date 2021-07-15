#include <stdlib.h>#include <stdio.h>#include <string.h>#include <math.h>#include <mandragora/astro/astrology.h>const int astro_default_planets[16] = {	ASTRO_SUN,	ASTRO_MOON,	ASTRO_MERCURY,	ASTRO_VENUS,	ASTRO_MARS,	ASTRO_JUPITER,	ASTRO_SATURN,	ASTRO_URANUS,	ASTRO_NEPTUNE,	ASTRO_PLUTO,	ASTRO_TNNODE,	ASTRO_CHIRON,	ASTRO_CERES,	ASTRO_ASCENDANT,	ASTRO_MC,-1};int astro_ruling_planets[ASTRO_NUM_ZODIAC] = {	ASTRO_MARS,	ASTRO_VENUS,	ASTRO_MERCURY,	ASTRO_MOON,	ASTRO_SUN,	ASTRO_MERCURY,	ASTRO_VENUS,	ASTRO_PLUTO,	ASTRO_JUPITER,	ASTRO_SATURN,	ASTRO_URANUS,	ASTRO_NEPTUNE};const int astro_planet_hierarchy[ASTRO_NUM_PLANETS] = { 0,4,1,2,3,5,6,7,8,9,10 };/** Ratios in grade difference between two planets for each aspect. */const double astro_aspect_ratios[ASTRO_NUM_ASPECTS] = {	0,							// ASTRO_CONJUNCTION			0		0°	30,						// ASTRO_SEMISEXTILE			1		30°		1/12	36,						// ASTRO_DECILE				2		36°		1/10	40,						// ASTRO_NOVILE				3		40°		1/9	45,						// ASTRO_SEMISQUARE			4		45°		1/8	360.0/7.0,				// ASTRO_SEPTILE				5		51°		1/7	60,						// ASTRO_SEXTILE				6		60°		1/6	72,						// ASTRO_QUINTILE				7		72°		1/5	90,						// ASTRO_SQUARE				8		90°		1/4	120,						// ASTRO_TRINE					9		120°		1/3	135,						// ASTRO_SESQUIQUADRATE		10		135°		3/8	150,						// ASTRO_QUINCUNX				11		150°		5/12	180						// ASTRO_OPPOSITION			12		180°		1/2};/** The differece between signs for aspects, i.e. for conjunction it is 0 and for opposition * it is 6 signs between planets in the aspect. Where not appliable value is -1. */const int astro_aspect_signs[ASTRO_NUM_ASPECTS] = { 0,1,-1,-1,-1,-1,2,-1,3,4,-1,-1,6 };/** For each aspect there are 4 values, these are used where any of the * planets involved in the aspect are: *  0: Sun or Moon. *  1: Ascendant. *  2: MC. *  3: Ruling planet of the Ascendant. *  4: Ruling planet of the Sun or Moon. *  5: Mercury, Venus or Mars. *  6: Jupiter or Saturn. *  7: Uranus, Neptune, Pluto. *  8: Nodes. *  9: Used for all other aspects. *  * A value set to <0 means the group of planets will not be used for aspects. */double astro_aspect_orbs[ASTRO_NUM_ASPECTS*ASTRO_ASPECT_ORB_LEVELS] = {//   0  | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9//  sun |asc | mc |rul-|rul-|mer |jup |ura |moon|etc//  moon|    |    |asc |sun |ven |sat |nep |node|//      |    |    |    |moon|mar |    |plu |    |	10.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,			// ASTRO_CONJUNCTION	 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,			// ASTRO_SEMISEXTILE	 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,			// ASTRO_DECILE	 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,			// ASTRO_NOVILE	 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,			// ASTRO_SEMISQUARE	 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,			// ASTRO_SEPTILE	 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0, 6.0,			// ASTRO_SEXTILE	 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,			// ASTRO_QUINTILE	 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,			// ASTRO_SQUARE	 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,			// ASTRO_TRINE	 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,			// ASTRO_SESQUIQUADRATE	 3.0, 2.0, 3.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0,			// ASTRO_QUINCUNX	10.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0, 8.0,			// ASTRO_OPPOSITION};/** Index of a planet in the astro_aspect_orbs array. */const int astro_aspect_orb_planet_index[ASTRO_NUM_PLANET_POINTS] = { 0,0,0,5,5,5,6,6,7,7,7,8,8,8,8,9,9,9,9,9,9,9,9,1,2,9,9,9 };const int astro_quality[ASTRO_NUM_ZODIAC] = { ASTRO_CARDINAL,ASTRO_FIXED,ASTRO_MUTABLE,ASTRO_CARDINAL,ASTRO_FIXED,ASTRO_MUTABLE,ASTRO_CARDINAL,ASTRO_FIXED,ASTRO_MUTABLE,ASTRO_CARDINAL,ASTRO_FIXED,ASTRO_MUTABLE };const int astro_element[ASTRO_NUM_ZODIAC] = { ASTRO_FIRE,ASTRO_EARTH,ASTRO_AIR,ASTRO_WATER,ASTRO_FIRE,ASTRO_EARTH,ASTRO_AIR,ASTRO_WATER,ASTRO_FIRE,ASTRO_EARTH,ASTRO_AIR,ASTRO_WATER };const int astro_energy[ASTRO_NUM_ZODIAC] = { ASTRO_MALE,ASTRO_FEMALE,ASTRO_MALE,ASTRO_FEMALE,ASTRO_MALE,ASTRO_FEMALE,ASTRO_MALE,ASTRO_FEMALE,ASTRO_MALE,ASTRO_FEMALE,ASTRO_MALE,ASTRO_FEMALE };void astro_set_ruling_planets(const int pl[ASTRO_NUM_ZODIAC]) {	memcpy(astro_ruling_planets,pl,sizeof(int)*ASTRO_NUM_ZODIAC);}void astro_set_aspect_orbs(const double orbs[ASTRO_NUM_ASPECTS*ASTRO_ASPECT_ORB_LEVELS]) {	memcpy(astro_aspect_orbs,orbs,sizeof(double)*ASTRO_NUM_ASPECTS*ASTRO_ASPECT_ORB_LEVELS);}double astro_midheaven(double ra,double ob) {	double x = atan(tan(ra)/cos(ob));	if(x<0) x = x+PI;	if(sin(ra)<0) x = x+PI;	return mod360(x*RTD);}double astro_ascendant(double ra,double ob,double la) {	double a = atan(cos(ra)/(-sin(ra)*cos(ob)-tan(la)*sin(ob)));	if(a<0) a = a+PI;	if(cos(ra)<0) a = a+PI;	return mod360(a*RTD);}double astro_fortune(double p1,double p2,double p3) {	double f = p1+p2-p3;	return f>360? f-360 : (f<0? f+360 : f);}double astro_eastpoint(double ra,double ob) {	return astro_ascendant(ra,ob,0);}double astro_vertex(double ra,double ob,double la) {	double x = cos(ra+PI);	double y = -sin(ra+PI)*cos(ob)-sin(ob)/tan(la);	double vt = atan(x/y);	if(vt<0) vt = vt+PI;	if(x<0) vt = vt+PI;	return vt*RTD;}static double plac(double ff,double y,double r1,double ra,double ob,double la) {	int i;	double x = -1,xx,r2,a,lo;//fprintf(out,"Astrology::plac(ff=%lf,y=%lf,r1=%lf,ra=%lf,ob=%lf,la=%lf)\n",ff,y,r1,ra,ob,la);//fflush(out);	if(y==1) x = 1;	for(i=1; i<11; i++) {		a = x*sin(r1)*tan(ob)*tan(la);//fprintf(out,"Astrology::plac(sin(r1)=%lf,tan(ob)=%lf,tan(la)=%lf,a=%lf,1-a*a=%lf,sqrt=%lf,atan=%lf)\n",//	sin(r1),tan(ob),tan(la),a,1-a*a,sqrt(1-a*a),atan(sqrt(1-a*a)/a));//fflush(out);		xx = acs(x*sin(r1)*tan(ob)*tan(la));		if(xx<0) xx = xx+PI;		r2 = ra+(xx/ff);		if(y==1) r2 = ra+PI-(xx/ff);		r1 = r2;//fprintf(out,"Astrology::plac(xx=%lf,r1=%lf)\n",xx,r1);//fflush(out);	}//fprintf(out,"Astrology::plac(r1=%lf)\n",r1);//fflush(out);	lo = atan(tan(r1)/cos(ob));//fprintf(out,"Astrology::plac(lo=%lf)\n",lo);//fflush(out);	if(lo<0) lo = lo+PI;	if(sin(r1)<0) lo = lo+PI;//fprintf(out,"Astrology::plac(lo=%lf)\n",lo);//fflush(out);	return lo*RTD;}int astro_placidus(astro_house *h,double ra,double ob,double la) {	int i;	double mc = astro_midheaven(ra,ob);//fprintf(out,"Astrology::placidus(ra=%lf,ob=%lf,la=%lf)\n",ra,ob,la);//fflush(out);	h[0].cusp = astro_ascendant(ra,ob,la);//fprintf(out,"astro_placidus(plac=%lf,mod360=%lf)\n",//	plac(1.5,1,ra+120*DTR,ra,ob,la),mod360(plac(1.5,1,ra+120*DTR,ra,ob,la)));//fflush(out);	h[1].cusp = mod360(plac(1.5,1,ra+120*DTR,ra,ob,la));	h[2].cusp = mod360(plac(3,1,ra+150*DTR,ra,ob,la));	h[3].cusp = mod360(mc+180);	h[4].cusp = mod360(plac(3,0,ra+30*DTR,ra,ob,la)+180);	h[5].cusp = mod360(plac(1.5,0,ra+60*DTR,ra,ob,la)+180);	for(i=6; i<12; i++) h[i].cusp = mod360(h[i-6].cusp+180);	return 1;}//kochint astro_koch(astro_house *h,double ra,double ob,double la) {	int i;	double a1 = asn(sin(ra)*tan(la)*tan(ob)),d,a2,kn,a3,x;	for(i=0; i<12; i++) {		d = mod360(60+30*(i+1));		a2 = d/90-1;kn = 1;		if(d>=180) { kn=-1;a2=d/90-3; }		a3 = mod360(ra*RTD+d+a2*a1*RTD)*DTR;		x = atan(sin(a3)/(cos(a3)*cos(ob)-kn*tan(la)*sin(ob)));		if(x<0) x = x+PI;		if(sin(a3)<0) x = x+PI;		h[i].cusp = mod360(x*RTD);	}	return 1;}int astro_zodiac(double l) {	int s = (int)(l<30? ASTRO_ARIES : (l-fmod(l,30))/30);	return s<ASTRO_ARIES || s>ASTRO_PISCES? ASTRO_ARIES : s;}double astro_angle(double p1,double p2) {	return p1>p2? p1-p2 : p2-p1;}double astro_composite_angle(double a1,double a2) {	double a;	if(a2<a1) a = a2,a2 = a1,a1 = a;	if(a1+360-a2<a2-a1) a1 += 360,a = a2,a2 = a1,a1 = a;	return mod360(a1+(a2-a1)/2);}