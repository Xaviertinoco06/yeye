#include <iostream>
#include <string>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <Windows.h>

using namespace std;

int jugar();
int menu();
int ancho = 1024;
int alto = 768;

ALLEGRO_DISPLAY* ventana;
ALLEGRO_FONT* fuente;
ALLEGRO_TIMER* segundoTimer;
ALLEGRO_TIMER* fps;
ALLEGRO_EVENT_QUEUE* event_queue;

int main() {

	if (!al_init()) {
		al_show_native_message_box(NULL, "ERROR CRITICO", "ERROR: 404", "No se pudo cargar correctamente la libreria alelgro", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}
	al_install_audio();
	al_init_acodec_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();
	al_init_image_addon();
	al_reserve_samples(2);

	

	ventana = al_create_display(ancho, alto);
	fuente = al_load_font("fuente/pokemon_pixel_font.ttf", 70, 0);

	int ancho_W = GetSystemMetrics(SM_CXSCREEN);
	int alto_W = GetSystemMetrics(SM_CYSCREEN);

	al_set_window_title(ventana, "Mi Juego");
	al_set_window_position(ventana, ancho_W / 2 - ancho / 2, alto_W / 2 - alto / 2);


	segundoTimer = al_create_timer(1.0);
	fps = al_create_timer(1.0 / 30);

	event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_timer_event_source(fps));
	al_register_event_source(event_queue, al_get_timer_event_source(segundoTimer));
	al_register_event_source(event_queue, al_get_mouse_event_source());
	

	
	al_start_timer(fps);
	al_start_timer(segundoTimer);

	menu();


	return 0;
}
void FundidoANegro(ALLEGRO_BITMAP* img)
{
	// Muestra la imagen y realiza un fundido a Negro

	int anchoImg = al_get_bitmap_width(img);
	int altoImg = al_get_bitmap_height(img);
	ALLEGRO_BITMAP* imgNegro = al_create_bitmap(anchoImg, altoImg);
	al_set_target_bitmap(imgNegro);
	al_clear_to_color(al_map_rgb_f(0, 0, 0));

	al_set_target_backbuffer(ventana);

	int alfa;
	for (int i = 0; i < 255; i++)
	{
		alfa = 255 - i;
		al_draw_bitmap(img, 0, 0, 0);
		al_draw_tinted_bitmap(imgNegro, al_map_rgba_f(0, 0, 0, alfa), 0, 0, 0);

		al_flip_display();
		al_rest(0.01);
		if (i == 0 || i == 254)
		{
			al_rest(2);
		}
	}
	al_destroy_bitmap(imgNegro);

	//Esta es una funcionalidad que obtiene como parámetro un bitmap que es la imagen inicial que se muestra a la cual se hace el fundido a negro. 
	//Primero se crea una imagen con las mismas magnitudes que la imagen recibida y se pinta de color negro, esta imagen es llamada imgNegro.

	//YEYE VOS SABES
}

int jugar()

{

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_filled_circle(200, 200, 100, al_map_rgb(255, 255, 255));
		al_flip_display();

	}
	return 1;
}
int menu() {
	int segundos = 0;
	int x = -1, y = -1;
	ALLEGRO_COLOR blanco = al_map_rgb(255, 255, 255);
	ALLEGRO_COLOR azar = al_map_rgb(255, 50, 65);

	ALLEGRO_BITMAP* menu_null = al_load_bitmap("imagenes/menu_null.png");
	ALLEGRO_BITMAP* menu_jugar = al_load_bitmap("imagenes/menu_jugar.png");
	ALLEGRO_BITMAP* menu_salir = al_load_bitmap("imagenes/menu_salir.png");
	ALLEGRO_BITMAP* yeye = al_load_bitmap("imagenes/YEYE.jpg");
	ALLEGRO_SAMPLE* efecto = al_load_sample("sonidos/efecto_menu.wav");
	ALLEGRO_SAMPLE* musica = al_load_sample("sonidos/menu.wav");

	ALLEGRO_SAMPLE_INSTANCE* insmusica = al_create_sample_instance(musica);
	al_set_sample_instance_playmode(insmusica, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(insmusica, al_get_default_mixer());


	//menu
	int botones[] = { 0 };

	while (true)
	{
		ALLEGRO_EVENT Evento;
		al_wait_for_event(event_queue, &Evento);
		al_play_sample_instance(insmusica);

		if (Evento.type == ALLEGRO_EVENT_TIMER) {
			if (Evento.timer.source == segundoTimer) {
				segundos++;
			}
		}
		al_clear_to_color(al_map_rgb(0, 0, 0));

		if (botones[0] == 0)
			al_draw_bitmap(menu_null, 0, 0, 0);
		else if (botones[0] == 1)
			al_draw_bitmap(menu_jugar, 0, 0, 0);
		else
			al_draw_bitmap(yeye, 0, 0, 0);
		

		if (Evento.type == ALLEGRO_EVENT_MOUSE_AXES || Evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{

			x = Evento.mouse.x;
			y = Evento.mouse.y;

			if (x >= 193 && x <= 874 && y >= 347 && y <= 462) {
				botones[0] = 1;
				if (Evento.mouse.button & 1)
					
					jugar();
				FundidoANegro(yeye);
				al_play_sample(efecto, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE,0);
			}
			else {
				if (x >= 193 && x <= 874 && y >= 495 && y <= 610) {
					botones[0] = 2;
					if (Evento.mouse.button & 1)
						
						return 1;
					al_play_sample(efecto, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
				}
				else {
					botones[0] = 0;
				}

			}

		}
	
		
		

		al_flip_display();
	}
	al_destroy_sample(efecto);
}

    
