#include <gtk/gtk.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "src/image/image.h"
#include "src/image/binarization.h"
#include "src/segmentation/segmentation.h"
#include "src/ml/struct/networks.h"
#include "src/rotate/rotate.h"
#include "src/matrix/matrix.h"

GtkWidget *window;
GtkWidget *Binarization;
GtkWidget *Read_text;
GtkWidget *Save;
GtkWidget *img_input;
GtkWidget *save_name;
GtkWidget *image;
GtkWidget *rotate_plus_5;
GtkWidget *rotate_minus_5;
GtkWidget *rotate_minus_90;
GtkWidget *rotate_plus_90;
GtkWidget *sharpness_plus;
GtkWidget *contrast_minus;
GtkWidget *contrast_plus;
GtkWidget *reload_image;
GtkTextView *text;
GtkBuilder *builder;

char *save_file_name;
char *imagepath;
SDL_Surface *image_surface;
struct Characters *segmentation_image;
struct Networks *networks;

// Main function.
int main()
{
	char cwd[500];
	char *networkpath = strcat(getcwd(cwd, sizeof(cwd)), "/data/networks/~training/network_1608069683.json");
	networks = LoadNetworksFromJSON(networkpath);
	// Initializes GTK.
	gtk_init(NULL, NULL);

	builder = gtk_builder_new_from_file("OCR_project.glade");

	window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

	gtk_builder_connect_signals(builder, NULL);

	Binarization = GTK_WIDGET(gtk_builder_get_object(builder, "binarization"));
	Read_text = GTK_WIDGET(gtk_builder_get_object(builder, "Read_text"));
	Save = GTK_WIDGET(gtk_builder_get_object(builder, "Save"));
	img_input = GTK_WIDGET(gtk_builder_get_object(builder, "img_input"));
	save_name = GTK_WIDGET(gtk_builder_get_object(builder, "save_name"));
	text = GTK_WIDGET(gtk_builder_get_object(builder, "text"));
	rotate_plus_5 = GTK_WIDGET(gtk_builder_get_object(builder, "rotate_plus_5"));
	rotate_minus_5 = GTK_WIDGET(gtk_builder_get_object(builder, "rotate_minus_5"));
	rotate_minus_90 = GTK_WIDGET(gtk_builder_get_object(builder, "rotate_minus_90"));
	rotate_plus_90 = GTK_WIDGET(gtk_builder_get_object(builder, "rotate_plus_90"));
	sharpness_plus = GTK_WIDGET(gtk_builder_get_object(builder, "sharpness_plus"));
	contrast_minus = GTK_WIDGET(gtk_builder_get_object(builder, "contrast_minus"));
	contrast_plus = GTK_WIDGET(gtk_builder_get_object(builder, "contrast_plus"));
	reload_image = GTK_WIDGET(gtk_builder_get_object(builder, "reload_img"));

	gtk_widget_show(window);

	gtk_main();

	return EXIT_SUCCESS;
}

void activate_buttons()
{
	gtk_widget_set_sensitive(rotate_plus_5, TRUE);
	gtk_widget_set_sensitive(rotate_minus_5, TRUE);
	gtk_widget_set_sensitive(rotate_minus_90, TRUE);
	gtk_widget_set_sensitive(rotate_plus_90, TRUE);
	gtk_widget_set_sensitive(sharpness_plus, TRUE);
	gtk_widget_set_sensitive(contrast_minus, TRUE);
	gtk_widget_set_sensitive(contrast_plus, TRUE);
	gtk_widget_set_sensitive(save_name, TRUE);
	gtk_widget_set_sensitive(Binarization, TRUE);
	gtk_widget_set_sensitive(Read_text, TRUE);
	gtk_widget_set_sensitive(Save, TRUE);
	gtk_widget_set_sensitive(reload_image, TRUE);
}

void desactivate_buttons()
{
	gtk_widget_set_sensitive(rotate_plus_5, FALSE);
	gtk_widget_set_sensitive(rotate_minus_5, FALSE);
	gtk_widget_set_sensitive(rotate_minus_90, FALSE);
	gtk_widget_set_sensitive(rotate_plus_90, FALSE);
	gtk_widget_set_sensitive(sharpness_plus, FALSE);
	gtk_widget_set_sensitive(contrast_minus, FALSE);
	gtk_widget_set_sensitive(contrast_plus, FALSE);
	gtk_widget_set_sensitive(save_name, FALSE);
	gtk_widget_set_sensitive(Binarization, FALSE);
	gtk_widget_set_sensitive(Read_text, FALSE);
	gtk_widget_set_sensitive(Save, FALSE);
	gtk_widget_set_sensitive(reload_image, FALSE);
}

void on_binarization_clicked(GtkButton *b)
{
	if (imagepath != NULL)
	{
		if (image_surface == NULL)
			image_surface = loadImage(imagepath);
		if (segmentation_image == NULL)
			segmentation_image = Segmentation(image_surface);
		desactivate_buttons();
		ShowImg(segmentation_image->Image_Segmentate);
		activate_buttons();
	}
}

void on_Read_text_clicked(GtkButton *b)
{
	if (imagepath == NULL)
		return;
	if (image_surface == NULL)
			image_surface = loadImage(imagepath);
	if (segmentation_image == NULL)
		segmentation_image = Segmentation(image_surface);

	FindCharacters(networks, segmentation_image);

	GtkTextBuffer *textbuffer = gtk_text_buffer_new(gtk_text_tag_table_new());
	gtk_text_buffer_set_text(textbuffer, segmentation_image->AllCharacters, segmentation_image->Nb_Characters);
	gtk_text_view_set_buffer(text, textbuffer);
}

void on_Save_clicked(GtkButton *b)
{
	if (save_file_name == NULL)
		return;
	GtkTextIter start;
	GtkTextIter end;
	GtkTextBuffer *savebuffer;
	savebuffer = gtk_text_view_get_buffer(text);
	gtk_text_buffer_get_start_iter(savebuffer, &start);
	gtk_text_buffer_get_end_iter(savebuffer, &end);
	int len = gtk_text_buffer_get_char_count(savebuffer);
	char *ai_text = gtk_text_buffer_get_text(savebuffer, &start, &end, FALSE);
	if (ai_text != NULL)
	{
		FILE *save = fopen(save_file_name, "w");
		while (len > 0)
		{
			len--;
			fputc(*ai_text, save);
			(ai_text)++;
		}
		
		fclose(save);
	}
}

void on_img_input_file_set(GtkFileChooserButton *f)
{
	if (imagepath != NULL)
		free(imagepath);
	imagepath = malloc(300 * sizeof(char));
	sprintf(imagepath, "%s", gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(f)));
	image_surface = loadImage(imagepath);
	activate_buttons();

}

void on_save_name_changed(GtkEntry *e)
{
	if (save_file_name != NULL)
		free(save_file_name);
	save_file_name = malloc(128 * sizeof(char));
	sprintf(save_file_name, "text/%s", gtk_entry_get_text(e));
}

// called when window is closed
void on_window_main_destroy()
{
	gtk_main_quit();
}

void on_reload_img_clicked(GtkButton *b)
{
	if (imagepath != NULL)
	{
		if (image_surface != NULL)
			SDL_FreeSurface(image_surface);
		if (segmentation_image != NULL)
			free(segmentation_image);
		segmentation_image = NULL;
		image_surface = loadImage(imagepath);
		ShowImg(image_surface);
	}
}

void on_sharpness_plus_clicked(GtkButton *b)
{
	desactivate_buttons();
	if (image_surface == NULL)
		return;
	image_surface = MedianFilter(image_surface, 3);
	ShowImg(image_surface);
	activate_buttons();
}

void on_contrast_plus_clicked(GtkButton *b)
{
	desactivate_buttons();
	if (image_surface == NULL)
		return;
	image_surface = PowerLaw(image_surface, 1, 1.1);
	ShowImg(image_surface);
	activate_buttons();
}

void on_contrast_minus_clicked(GtkButton *b)
{
	desactivate_buttons();
	if (image_surface == NULL)
		return;
	image_surface = PowerLaw(image_surface, 1, 0.9);
	ShowImg(image_surface);
	activate_buttons();
}

void rotation(int angle)
{
	desactivate_buttons();
	if (image_surface == NULL)
		return;
	struct MatrixUCHAR im_matR = createMatrixUCHAR(image_surface->w, image_surface->h);
	struct MatrixUCHAR im_matG = createMatrixUCHAR(image_surface->w, image_surface->h);
	struct MatrixUCHAR im_matB = createMatrixUCHAR(image_surface->w, image_surface->h);
	for (int i = 0; i < im_matR.rows; i++)
	{
		for (int j = 0; j < im_matR.columns; j++)
		{
			SDL_Color color;
			Uint32 pixel = getPixel(image_surface, i, j);
			SDL_GetRGB(pixel, image_surface->format, &color.r, &color.g, &color.b);
			matrixSetUCHAR(im_matR, i, j, color.r);
			matrixSetUCHAR(im_matG, i, j, color.g);
			matrixSetUCHAR(im_matB, i, j, color.b);
		}
	}
	im_matR = rotateUCHAR(im_matR, angle);
	im_matG = rotateUCHAR(im_matG, angle);
	im_matB = rotateUCHAR(im_matB, angle);

	SDL_FreeSurface(image_surface);
	image_surface = SDL_CreateRGBSurface(0, im_matR.rows, im_matR.columns, 32, 0, 0, 0, 0);

	for (int i = 0; i < im_matR.rows; i++)
	{
		for (int j = 0; j < im_matR.columns; j++)
		{
			unsigned char r = matrixGetUCHAR(im_matR, i, j);
			unsigned char g = matrixGetUCHAR(im_matG, i, j);
			unsigned char b = matrixGetUCHAR(im_matB, i, j);
			SDL_Rect rect = {i, j, 1, 1};
			SDL_FillRect(image_surface, &rect, SDL_MapRGB(image_surface->format, r, g, b));
		}
	}
	ShowImg(image_surface);
	activate_buttons();
}

void on_rotate_plus_5_clicked(GtkButton *b)
{ rotation(5); }

void on_rotate_minus_5_clicked(GtkButton *b)
{ rotation(-5); }

void on_rotate_plus_90_clicked(GtkButton *b)
{ rotation(90); }

void on_rotate_minus_90_clicked(GtkButton *b)
{ rotation(-90); }