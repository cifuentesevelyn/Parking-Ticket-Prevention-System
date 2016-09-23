#include <gtk/gtk.h>
#include <glib.h>
#include <time.h>

const int NUM_SECONDS = 2; 

int main(int argc, char *argv[]) {
	
	int a;
  
    double time_counter = 0;
    
    clock_t this_time = clock();
    clock_t last_time = this_time;

    printf("Gran = %ld\n", NUM_SECONDS * CLOCKS_PER_SEC);
   
    while(1){
    this_time = clock();

    time_counter += (double)(this_time - last_time);

    last_time = this_time;

    if(time_counter > (double)(NUM_SECONDS * CLOCKS_PER_SEC))
    {
          time_counter -= (double)(NUM_SECONDS * CLOCKS_PER_SEC);
          a = 1;
          printf("a = %d\n", a);
		  
    if(a == 1){

	FILE *file, *rfile;
    FILE *output;
    file = fopen("lcd.txt", "r"); // opens file for reading
	rfile = fopen("nopass.txt", "r");
    output = fopen("outputlcd.txt", "w"); // opens file for writing

    char lcd[32];
	char pass[32];

   while (fgets(lcd, 32, file) && fgets(pass, 32, rfile) ) {

	int capacity = atoi(lcd);
	int nopass = atoi(pass);
    int lot_numb = 10;

  GtkWidget *window;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *label3;
  GtkWidget *hseparator;
  GtkWidget *vbox;
  GtkWidget *button;

  GtkWidget* gtk_separator_new (GtkOrientation orientation); 

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Lot Capacity");
  gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
  gtk_container_set_border_width(GTK_CONTAINER(window), 60);

  int suggest = 11;
  
  char msg[32]={0};
  g_snprintf(msg, sizeof msg, "Lot %d capacity %d\n", lot_numb, capacity);
  label1 = gtk_label_new(msg);
  gtk_widget_modify_font (label1, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label1), TRUE);
  
  if(capacity < 30){
  label2 = gtk_label_new("Spots Available\n");
  gtk_widget_modify_font (label2, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);
  }

  if(capacity >= 30){
  char msg2[32]={0};
  g_snprintf(msg2, sizeof msg2, "Lot %d is Filling Up\n", lot_numb);
  label2 = gtk_label_new(msg2);
  gtk_widget_modify_font (label2, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);
  }
  
  if(capacity == 39){
  label2 = gtk_label_new("One Spot Available\n");
  gtk_widget_modify_font (label2, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);
  }

  if(capacity == 40){
  char msg1[32]={0};
  g_snprintf(msg1, sizeof msg1, "Lot %d Full: Park in Lot %d\n", lot_numb, suggest);
  label2 = gtk_label_new(msg1);
  gtk_widget_modify_font (label2, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label2), TRUE);
  }
  if(nopass == 1){
  label3 = gtk_label_new("Pass Invalid: Pay To Park\n");
  gtk_widget_modify_font (label3, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label3), TRUE);
  }
  if(nopass == 0){
  char msg3[32]={0};
  g_snprintf(msg3, sizeof msg3, "Welcome to Lot %d\n", lot_numb);  
  label3 = gtk_label_new(msg3);
  gtk_widget_modify_font (label3, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label3), TRUE);
  } 
  if(nopass == 2){
  label3 = gtk_label_new("No Pass: Pay To Park\n");
  gtk_widget_modify_font (label3, pango_font_description_from_string ("Monospace 10"));
  gtk_label_set_line_wrap(GTK_LABEL(label3), TRUE);
  }
  
  button = gtk_button_new_with_label("UPDATE");
  gtk_widget_set_size_request(button, 20, 20);
  
  vbox = gtk_box_new(FALSE, 10);
  gtk_container_add(GTK_CONTAINER(window), vbox);

  
 hseparator = gtk_hseparator_new();

  
  gtk_box_pack_start(GTK_BOX(vbox), label1, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), hseparator, FALSE, TRUE, 10);
  gtk_box_pack_start(GTK_BOX(vbox), label2, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), label3, FALSE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, TRUE, 0);
 
  g_signal_connect(G_OBJECT(button), "clicked",
      G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  g_signal_connect(G_OBJECT(window), "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  g_signal_connect_swapped(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), G_OBJECT(window));

  gtk_widget_show_all(window);

  gtk_main();
  
	} //end of while loop
    fclose(rfile);
    fclose(file);
    fclose(output);
  } //end of b = 1
          else{
            a = 0;
            }
             // close the files
    
 } //end of if loop to make b = 1
	}
 return 0;
}
