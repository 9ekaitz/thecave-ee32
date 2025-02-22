#define _CRT_SECURE_NO_WARNINGS
#include "Basic.h"
#include "Motion.h"
#include "Event.h"
#include "Image.h"
#include <string.h>
#include <stdio.h>
#include "Sound.h"

HITBOX hitbox;//

extern PERTSONAIA pertsonaia;
extern ETSAIA etsaia[ETSAI_KOPURUA + 1];
extern TIROAK jaurtigai[30];


extern BOSSFIGHT faseak;

extern int IrudiZnbk;

int kont;

SDL_bool a = SDL_FALSE;
SDL_bool d = SDL_FALSE;
SDL_bool espacio = SDL_FALSE;
SDL_bool k = SDL_FALSE;
SDL_bool w = SDL_FALSE;
SDL_bool f3 = SDL_FALSE;
SDL_bool s = SDL_FALSE;
SDL_bool gora = SDL_FALSE;
SDL_bool behera = SDL_FALSE;

ROL Ordenagailua;

void EbentuakKonprobatu(SDL_bool* Jokatzen, PANTAILAK* Pantaila, int* pAnimazioa, ZENTZUA* begira, int BizirikDaudenEtsaiak[], int BizirikKopurua)
{	
	SDL_bool enter = SDL_FALSE;
	

	SAGUA klika;
	SDL_Event ebentua;
	do
	{
		while (SDL_PollEvent(&ebentua))
		{
			switch (ebentua.type)
			{
				//*Pantaila += 1;//esto no sirve de nada
			case SDL_QUIT:
				Amaitu(Jokatzen, Pantaila);
				break;
			case SDL_MOUSEBUTTONUP:
				ZeinKlikatuDa(ebentua.button, &klika);
				KonprobatuKlika(Pantaila, klika, Jokatzen);
				break;
			case SDL_KEYDOWN:
				switch (ebentua.key.keysym.scancode)		// SWITCH PARA LAS PULSACIONES DE TECLAS
				{
				case SDL_SCANCODE_D:
					a = SDL_FALSE;
					if (!d && !pertsonaia.erortzen && !pertsonaia.salto && pertsonaia.sprite != HIL)//si no se esta callendo o esta en el aire se puede hacer
					{
						pertsonaia.sprite = KORRIKA;
						pertsonaia.erasotzen = SDL_FALSE;
						*pAnimazioa = 0;
					}
					d = SDL_TRUE;
					break;
				case SDL_SCANCODE_A:
					d = SDL_FALSE;
					if (!a && !pertsonaia.erortzen && !pertsonaia.salto && pertsonaia.sprite != HIL)
					{
						pertsonaia.sprite = KORRIKA;
						pertsonaia.erasotzen = SDL_FALSE;
						*pAnimazioa = 0;
					}
					a = SDL_TRUE;
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SDL_TRUE;
					break;
				case SDL_SCANCODE_K:
					if (!pertsonaia.erortzen && !pertsonaia.salto)
					{
						a = SDL_FALSE;
						d = SDL_FALSE;
					}

					if (!pertsonaia.erasotzen)
					{
						k = SDL_TRUE;
					}
					break;
				case SDL_SCANCODE_ESCAPE:
					Amaitu(Jokatzen, Pantaila);
					break;
				case SDL_SCANCODE_W:
					if (!a && !pertsonaia.erortzen && !pertsonaia.salto)
					{
						pertsonaia.erasotzen = SDL_FALSE;
					}
					w = SDL_TRUE;
					break;
				case SDL_SCANCODE_F3:
					f3 = !f3;
					break;
				case SDL_SCANCODE_S:
					s = SDL_TRUE;
					break;
				case SDL_SCANCODE_UP:
					gora = SDL_TRUE;
					break;
				case SDL_SCANCODE_DOWN:
					behera = SDL_TRUE;
					break;
				}
				break;
			case SDL_KEYUP:
				switch (ebentua.key.keysym.scancode)
				{
				case SDL_SCANCODE_D:
					d = SDL_FALSE;
					break;
				case SDL_SCANCODE_A:
					a = SDL_FALSE;
					break;
				case SDL_SCANCODE_SPACE:
					espacio = SDL_FALSE;
					break;
				case SDL_SCANCODE_K:
					k = SDL_FALSE;
					break;
				case SDL_SCANCODE_W:
					w = SDL_FALSE;
					break;
				case SDL_SCANCODE_S:
					s = SDL_FALSE;
					break;
				case SDL_SCANCODE_UP:
					gora = SDL_FALSE;
					break;
				case SDL_SCANCODE_DOWN:
					behera = SDL_FALSE;
					break;
				
				case SDL_SCANCODE_RETURN:
					if (pertsonaia.bizirik)
					{
						if (!enter)
						{
							ImgKargatu(".\\media\\menu\\Pausa.bmp", 56, 67, 1200, 630);
							RenderPrestatu(*begira, BizirikDaudenEtsaiak, BizirikKopurua);
							Irudikatu();
						}
						else
						{
							IrudiZnbk = IrudiakKendu(IrudiZnbk - 1);//esto borra la ultima imagen (el pause de arriba)
						}
						enter = !enter;
					}
				break;
			
				
				}
				break;
			}
			
		}
		if (enter)
		{
			SDL_Delay(100); //cuando el juego se pausa se queda en un bucle infinito y los eventos se comprueban cada 100 milisegundos
		}
	}while (enter);
}

void ZeinKlikatuDa(SDL_MouseButtonEvent ebentua, SAGUA* klika)
{
	switch (ebentua.button)
	{
	case SDL_BUTTON_LEFT:
		*klika = EZKER;
		break;

	case SDL_BUTTON_RIGHT:
		*klika = ESKUIN;
		break;

	case SDL_BUTTON_MIDDLE:
		*klika = ERDIA;
		break;
	}
}

void KonprobatuKlika(PANTAILAK* Pantaila, SAGUA klika, SDL_bool *Jokatzen)
{
	int x, y;
	switch (*Pantaila)
	{
	case MENUA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 515 && y > 175) && (x < 765 && y < 275))
			{
				RenderPrestatu(AURRERA, 0, 0);
				Irudikatu();
				PertsonaiaHasieratu();
				EtsaiakHasieratu();
				Animazioa();
				*Pantaila = LEHEN;
			}
			else if ((x > 510 && y > 300) && (x < 760 && y < 400))
			{
				*Pantaila = KONTROLAK;
			}
			else if ((x > 512 && y > 425) && (x < 762 && y < 525))
			{
				*Pantaila = KREDITUAK;
			}
		}
		break;

	case KREDITUAK:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1063 && y > 99) && (x < 1109 && y < 142))
			{
				*Pantaila = MENUA;
			}
		}
		break;

	case KONTROLAK:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1063 && y > 99) && (x < 1109 && y < 142))
			{
				*Pantaila = MENUA;
				printf("MENUA\n");
			}
			else if ((x > 957 && y > 517) && (x < 1007 && y < 571))
			{
				printf("ENTRA\n");
				IrudiZnbk = IrudiakKendu(IrudiZnbk - 1);
				RenderPrestatu(AURRERA, 0, 0);
				Irudikatu();
			}
		}
		break;
	case ATERA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 494 && y > 443) && (x < 800 && y < 533))
			{
				*Pantaila = LEHEN;
			}
			else if ((x > 587 && y > 547) && (x < 705 && y < 582))
			{
				*Jokatzen = SDL_FALSE;
			}
		}
		break;
	case AUKERATUMODUA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 381 && y > 454) && (x < 578 && y < 578)) //ONLINE
			{
				*Pantaila = AUKERATUZERBITZUA;
			}
			if ((x > 705 && y > 454) && (x < 895 && y < 578)) //LOCAL
			{
				*Pantaila = MINIJOKOA;
			}
		}
		break;
	case AUKERATUZERBITZUA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 381 && y > 454) && (x < 578 && y < 578)) //CREATE
			{
				*Pantaila = AUKERAZERBITZARIA;
			}
			if ((x > 705 && y > 454) && (x < 895 && y < 578)) //JOIN
			{
				*Pantaila = AUKERABEZEROA;
			}
		}
		break;
	case AUKERAZERBITZARIA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1159 && y > 639) && (x < 1236 && y < 677))
			{
				*Pantaila = MINIJOKOA;
			}
		}
		break;
	case AUKERABEZEROA:
		if (klika == EZKER)
		{
			SDL_GetMouseState(&x, &y);
			if ((x > 1159 && y > 639) && (x < 1236 && y < 677))
			{
				*Pantaila = MINIJOKOA;
			}
		}
		break;
	}
}



void KolisioakKonprobatu(void* pixels, int pitch, Uint8 bpp, int BizirikDaudenEtsaiak[], int* BizirikKopurua, ZENTZUA begira, int* pAnimazioa)
{

	int PertzonaiaEzkerMuga = pertsonaia.DestSprite.x + 46;
	int PertzonaiaEskuinMuga = pertsonaia.DestSprite.x + 82;
	int PertzonaiaYGoikoa = pertsonaia.DestSprite.y;
	int PertzonaiaYBekoa = pertsonaia.DestSprite.y + 59;
	int YBekoa = pertsonaia.DestSprite.y + 52;
	int altuera = 0;
	int etsaiaxEzker;
	int etsaiaxEskuin;
	int	etsaiayGoikoa;
	int	etsaiayBehekoa;
	int j;

	for (j = 0; j < *BizirikKopurua; j++)
	{
		//detecta el tipo de enemigo
		if (BizirikDaudenEtsaiak[j] >= 0 && BizirikDaudenEtsaiak[j] <= 4)
		{
			altuera = 0;
		}
		else if (BizirikDaudenEtsaiak[j] >= 5 && BizirikDaudenEtsaiak[j] <= 9)
		{
			altuera = 7;
		}
		//DETECTAR A QUE LADO MIRA EL PERSONAGE

		etsaiaxEzker = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.x + 9;
		etsaiaxEskuin = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.x + 29;
		etsaiayGoikoa = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.y + altuera;
		etsaiayBehekoa = etsaia[BizirikDaudenEtsaiak[j]].DestSprite.y + 43;
		/*
				printf("etsaiaxEzker: %d\n", etsaiaxEzker);
				printf("etsaiaxEskuin: %d\n", etsaiaxEskuin);
				printf("etsaiayGoikoa: %d\n", etsaiayGoikoa);
				printf("etsaiayBehekoa: %d\n", etsaiayBehekoa);
				*/

		if (pertsonaia.sprite == ERASO && pertsonaia.erasotzen && *pAnimazioa > 4)
		{
			if (begira == AURRERA)
			{
				

				if ((etsaiaxEzker >= PertzonaiaEskuinMuga && etsaiaxEzker <= PertzonaiaEskuinMuga + 33) && ( PertzonaiaYGoikoa + 29 >= etsaiayGoikoa && PertzonaiaYGoikoa + 29  <= etsaiayBehekoa))
				{
					EtsaiaKendu(j, BizirikDaudenEtsaiak, *BizirikKopurua);
					--* BizirikKopurua;
				}
			}
			else
			{
				if ((etsaiaxEskuin >= PertzonaiaEzkerMuga - 33 && etsaiaxEskuin <= PertzonaiaEzkerMuga) && (PertzonaiaYGoikoa + 29 >= etsaiayGoikoa && PertzonaiaYGoikoa + 29 <= etsaiayBehekoa))
				{
					EtsaiaKendu(j, BizirikDaudenEtsaiak, *BizirikKopurua);
					--* BizirikKopurua;
				}
			}
		}
		if (((PertzonaiaEskuinMuga >= etsaiaxEzker && PertzonaiaEskuinMuga <= etsaiaxEskuin) || (PertzonaiaEzkerMuga <= etsaiaxEskuin && PertzonaiaEskuinMuga >= etsaiaxEzker)) && (PertzonaiaYBekoa >= etsaiayGoikoa && PertzonaiaYGoikoa <= etsaiayBehekoa))
		{
			if (pertsonaia.sprite != HIL)
			{
				*pAnimazioa = 0;
			}
			pertsonaia.sprite = HIL;
			
		}
	}

//////////////////////////////tetectar el color//////////////////////////////
hitbox.goikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 66, pertsonaia.DestSprite.y + 0);		//Burua
//Ezkerreko aldea
hitbox.ezker.goikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 46, pertsonaia.DestSprite.y + 11);

hitbox.ezker.erdikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 46, pertsonaia.DestSprite.y + 32);
hitbox.ezker.behekoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 46, pertsonaia.DestSprite.y + 52);
//Eskuineko aldea
hitbox.eskuin.goikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 82, pertsonaia.DestSprite.y + 11);
hitbox.eskuin.erdikoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 82, pertsonaia.DestSprite.y + 32);
hitbox.eskuin.behekoa = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 82, pertsonaia.DestSprite.y + 52);
//Behekoa
hitbox.behekoa.ezker = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 54, pertsonaia.DestSprite.y + 59);
hitbox.behekoa.eskuin = getpixel(pixels, pitch, bpp, pertsonaia.DestSprite.x + 75, pertsonaia.DestSprite.y + 59);
if (hitbox.behekoa.eskuin == GORRIA || hitbox.behekoa.ezker == GORRIA || hitbox.eskuin.behekoa == GORRIA || hitbox.ezker.behekoa == GORRIA)
{
	if (pertsonaia.sprite != HIL)
	{
		*pAnimazioa = 0;//se pone esto porque la animacion se repite sino
	}
	pertsonaia.sprite = HIL;
	pertsonaia.erortzen = SDL_FALSE;
	pertsonaia.salto = SDL_FALSE;
}
}


void KolisioakBoss(PANTAILAK* Pantaila, ZENTZUA begira, int* pAnimazioa, int* bAnimazioa, int BizirikDaudenEtsaiak[], int* BizirikKopurua, Uint32 *attackrate)
{
	static Uint32 spawnrate = 0;
	static SDL_bool spawn = SDL_FALSE;
	int PertzonaiaEzkerMuga = pertsonaia.DestSprite.x + 46;
	int PertzonaiaEskuinMuga = pertsonaia.DestSprite.x + 82;
	int PertzonaiaYGoikoa = pertsonaia.DestSprite.y;
	int PertzonaiaYBekoa = pertsonaia.DestSprite.y + 59;
	int YBekoa = pertsonaia.DestSprite.y + 52;

	for (int j = 0; j < 30; j++)
	{
		if ((jaurtigai[j].tiroa.x <= PertzonaiaEskuinMuga && jaurtigai[j].tiroa.x + 10 >= PertzonaiaEzkerMuga) && (jaurtigai[j].tiroa.y + 10 >= PertzonaiaYGoikoa && jaurtigai[j].tiroa.y <= PertzonaiaYBekoa))
		{
			if (pertsonaia.sprite != HIL)
			{
				*pAnimazioa = 0;
			}
			pertsonaia.sprite = HIL;
			break;//(a�adido despues) si te toca una bala nio merece la pena que los demas se comprueben
		}
	}
	if (pertsonaia.sprite == ERASO && pertsonaia.erasotzen && *pAnimazioa > 4 && (PertzonaiaYGoikoa + 29 >= BOSS.DestSprite.y && PertzonaiaYGoikoa + 29 <= BOSS.DestSprite.y + 149))
	{
		
		if (begira == AURRERA)
		{
			//cuando mira a la derecha
			if (BOSS.DestSprite.x + 16 >= PertzonaiaEskuinMuga && BOSS.DestSprite.x + 16 <= PertzonaiaEskuinMuga + 33)
			{

				if (faseak == SLEEP)
				{
					MusikaJOKUA(MusikaBOSS);

					faseak = TRANSFORM;
					*bAnimazioa = 0;
				}
				else if (SDL_TICKS_PASSED(SDL_GetTicks(), spawnrate) && faseak != TRANSFORM)
				{
					faseak = MUGITU;
					*attackrate = SDL_GetTicks() + 4000;
					kont++;
					spawn = SDL_TRUE;
					spawnrate = SDL_GetTicks() + 2000;
					Efektuak(BOOS_KOLPE_EFEKTUA);

				}
			}
		}
		else
			//cuando mira a la izquierda
		{
			if (BOSS.DestSprite.x + 109 >= PertzonaiaEzkerMuga - 33 && BOSS.DestSprite.x + 109 <= PertzonaiaEzkerMuga)
			{
				if (faseak == SLEEP)
				{
					MusikaJOKUA(MusikaBOSS);

					faseak = TRANSFORM;
					*bAnimazioa = 0;
				}
				else if (SDL_TICKS_PASSED(SDL_GetTicks(), spawnrate) && faseak != TRANSFORM)
				{
					faseak = MUGITU;
					*attackrate = SDL_GetTicks() + 4000;
					kont++;
					spawn = SDL_TRUE;
					spawnrate = SDL_GetTicks() + 2000;
					Efektuak(BOOS_KOLPE_EFEKTUA);
				}
				
			}
		}
	}
	if (faseak != SLEEP && (((PertzonaiaEskuinMuga >= BOSS.DestSprite.x + 16 && PertzonaiaEskuinMuga <= BOSS.DestSprite.x + 109) || (PertzonaiaEzkerMuga <= BOSS.DestSprite.x + 109 && PertzonaiaEskuinMuga >= BOSS.DestSprite.x + 16)) && (PertzonaiaYBekoa >= BOSS.DestSprite.y && PertzonaiaYGoikoa <= BOSS.DestSprite.y + 149)))
	{
		if (pertsonaia.sprite != HIL)
		{
			*pAnimazioa = 0;
		}
		pertsonaia.sprite = HIL;
	}
	if (SDL_TICKS_PASSED(SDL_GetTicks(), spawnrate) && spawn)
	{
		for (int i = 0; i < 10; i++)
		{
			if (!etsaia[i].bizirik)
			{
				EtsaiaKokatu(i, etsaia[i].DestSprite.x, etsaia[i].DestSprite.y, BizirikDaudenEtsaiak, BizirikKopurua);
			}
		}
		spawn = SDL_FALSE;
	}
	if (kont == 3)
	{
		PertsonaiaHil(kont);
		*Pantaila = ATERA;
	}
}