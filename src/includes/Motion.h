#ifndef MOTION_H
#define MOTION_H

#define GRABITATEA 18
#define ETSAI_KOPURUA 10
#define ABIADURA_MUKITXUA 2
#define ABIADURA_MAMUA 4
#define ETSAIA_SPRITE_KOPURUA 4

#define BOSS etsaia[ETSAI_KOPURUA]

typedef enum {ATZERA, AURRERA}ZENTZUA;
typedef enum { SLEEP, TRANSFORM, TRIGGERED, JAURTI, MUGITU, ITXARON}BOSSFIGHT;


void AltueraZuzendu(void* pixels, int pitch, Uint8 bpp);
void EtsaienAdimena(int znbk_etsaia, void* pixels, int pitch, Uint8 bpp);// sigue lineas IA
void Animazioa();		//Jokatu sakatzen denean aniamzio labur bat egiten du
void Ekintzak(int* pAnimazioa, ZENTZUA* begira, void* pixels, int pitch, Uint8 bpp, PANTAILAK* pantaila, int BizirikDaudenEtsaiak[], int* BizirikKopurua);
void EtsaiaKokatu(int znbk_etsaia, int x, int y, int BizirikDaudenEtsaiak[], int* BizirikKopurua);		//Etsaia nibel hasieran kokatu, etsaiaren zenbakia, x eta y posizioa emanez

void PertsonaiaMugitu(int* pAnimazioa, ZENTZUA* begira, PANTAILAK* pantaila);
void BossMugitu(int* bAnimazioa, int BizirikDaudenEtsaiak[], int* BizirikKopurua, Uint32* attackrate);


#endif