#include "header.h"
#include "gui.h"
#include "buttons.h"
#include "keyboard.h"

/* This creates all the GTK+ widgets that compose our application, and registers the callbacks */
void create_ui (CustomData *data)
 {
  GtkWidget *main_window;  /* The uppermost window, containing all other windows */
  GtkWidget *video_window; /* The drawing area where the video will be shown */
  GtkWidget *main_box;     /* VBox to hold main_hbox and the controls */
  GtkWidget *main_hbox;    /* HBox to hold the video_window and the stream info text widget */
  GtkWidget *controls, *controls1;     /* HBox to hold the buttons and the slider */
  GtkWidget *visualizer_button,*playpause_button, *start,*end,*play_button,*pause_button,*stop_button,*button_volume_up,   *button_volume_down,*next_button,*previous_button,*backward_button, *forward_button, *backward_button_5, *forward_button_5,
 *per_forward_button, *per_backward_button; /* Buttons */

  main_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  g_signal_connect (G_OBJECT (main_window), "delete-event", G_CALLBACK (delete_event_cb), data);

  video_window = gtk_drawing_area_new ();
  GdkScreen *screen = gdk_screen_get_default(); 
  GdkVisual *visual = gdk_screen_get_system_visual(screen);
  g_signal_connect (video_window, "realize", G_CALLBACK (realize_cb), data);
  g_signal_connect (video_window, "draw", G_CALLBACK (draw_cb), data);
  
  /*******************************visualizer*********************************/
  
   visualizer_button=gtk_button_new();
   GtkBox *visualizer_box=GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
   gtk_container_add(GTK_CONTAINER(visualizer_button), GTK_WIDGET(visualizer_box));
  
   GtkWidget *visualizer_icon = gtk_image_new_from_icon_name("audio-x-generic-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
   gtk_box_pack_start(visualizer_box, visualizer_icon, FALSE, FALSE, 0);
   GtkWidget *visualizer_label = gtk_label_new("Visualizer");
   gtk_box_pack_start(visualizer_box, visualizer_label, FALSE, FALSE, 0);
   g_signal_connect (G_OBJECT (visualizer_button), "clicked", G_CALLBACK (visualizer_cb), data);
  
  
  /*************************play-pause**********************************/
  
 
   playpause_button=gtk_button_new();
   GtkBox *playpause_box=GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
   gtk_container_add(GTK_CONTAINER(playpause_button), GTK_WIDGET(playpause_box));
   GtkWidget *play_icon = gtk_image_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_SMALL_TOOLBAR);
   gtk_box_pack_start(playpause_box, play_icon, FALSE, FALSE, 0);GtkWidget *play_label = gtk_label_new("Play/Pause");
   gtk_box_pack_start(playpause_box, play_label, FALSE, FALSE, 0);
   g_signal_connect (G_OBJECT (playpause_button), "clicked", G_CALLBACK (play_pause), data);
   gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
   g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_play_pause_cb), data);     
        
  /**********************Restart***************************************/
  
    stop_button=gtk_button_new();
  
   GtkBox *stop_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
   gtk_container_add(GTK_CONTAINER(stop_button), GTK_WIDGET(stop_button_box));
  
   GtkWidget *stop_icon = gtk_image_new_from_icon_name("media-playback-stop", GTK_ICON_SIZE_SMALL_TOOLBAR);
   gtk_box_pack_start(stop_button_box, stop_icon, FALSE, FALSE, 0);

   GtkWidget *stop_label = gtk_label_new("Restart");
   gtk_box_pack_start(stop_button_box, stop_label, FALSE, FALSE, 0);
   g_signal_connect (G_OBJECT (stop_button), "clicked", G_CALLBACK (stop_cb), data);
   gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
   g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_stop_cb), data);
  
  /*******************volume up ********************************************/
  
  button_volume_up=gtk_button_new();
  
  GtkBox *up_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(button_volume_up), GTK_WIDGET(up_button_box));
  
  GtkWidget *up_icon = gtk_image_new_from_icon_name("audio-volume-high", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(up_button_box, up_icon, FALSE, FALSE, 0);

  GtkWidget *up_label = gtk_label_new("+");
  gtk_box_pack_start(up_button_box, up_label, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (button_volume_up), "clicked", G_CALLBACK (volume_up_cb), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_volume_up_cb), data);
  
  /***********************volume down*************************************/
  
  button_volume_down=gtk_button_new();
  
  GtkBox *down_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(button_volume_down), GTK_WIDGET(down_button_box));
  
  GtkWidget *down_icon = gtk_image_new_from_icon_name("audio-volume-low", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(down_button_box, down_icon, FALSE, FALSE, 0);

  GtkWidget *down_label = gtk_label_new("-");
  gtk_box_pack_start(down_button_box, down_label, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (button_volume_down), "clicked", G_CALLBACK (volume_down_cb), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_volume_down_cb), data);
  
  /**************************** Create the volume slider*****************/
  data->volume_slider = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, 0, 10, 0.5);

  gtk_range_set_inverted(GTK_RANGE(data->volume_slider), TRUE);  // Invert the direction
  gtk_widget_set_size_request(data->volume_slider, 20, -1);

  // Connect the "value-changed" signal of the slider to a callback function
  g_signal_connect(G_OBJECT(data->volume_slider), "value-changed", G_CALLBACK(volume_slider_cb), data);

  // Set the padding and style of the volume_slider widget
  GtkStyleContext *context = gtk_widget_get_style_context(data->volume_slider);
  gtk_style_context_add_class(context, "volume-slider");
  gtk_style_context_add_class(context, "scale-horizontal");


  // Create the volume icon image
  GtkImage *icon = GTK_IMAGE(gtk_image_new_from_icon_name("audio-volume-high-symbolic", GTK_ICON_SIZE_LARGE_TOOLBAR));


  // Connect the "value-changed" signal of the slider to a callback function
  g_signal_connect(G_OBJECT(data->volume_slider), "value-changed", G_CALLBACK(volume_slider_cb), data); 
  //backward 60 -------------------------------------------------------------------------
  
  backward_button=gtk_button_new();
  GtkBox *backward_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(backward_button), GTK_WIDGET(backward_button_box));
  GtkWidget *backward_icon = gtk_image_new_from_icon_name("media-seek-backward-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(backward_button_box, backward_icon, FALSE, FALSE, 0);
  GtkWidget *backward_label = gtk_label_new("60-");
  gtk_box_pack_start(backward_button_box, backward_label, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (backward_button), "clicked", G_CALLBACK (backward_cb), data);
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_backward_cb), data);
  
  
  /*********************************forward 60 *********************************/
  
  forward_button=gtk_button_new();
  
  GtkBox *forward_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(forward_button), GTK_WIDGET(forward_button_box));
  
  GtkWidget *forward_label = gtk_label_new("60+");
  gtk_box_pack_start(forward_button_box, forward_label, FALSE, FALSE, 0);
  
  GtkWidget *forward_icon = gtk_image_new_from_icon_name("media-seek-forward-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(forward_button_box, forward_icon, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (forward_button), "clicked", G_CALLBACK (forward_cb), data);
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_forward_cb), data);
  
  /*************************************backward 5*********************************/
  
  backward_button_5=gtk_button_new();
  
  GtkBox *backward5_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(backward_button_5), GTK_WIDGET(backward5_button_box));
  
  GtkWidget *backward5_icon = gtk_image_new_from_icon_name("pan-start-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(backward5_button_box, backward5_icon, FALSE, FALSE, 0);

  GtkWidget *backward5_label = gtk_label_new("5-");
  gtk_box_pack_start(backward5_button_box, backward5_label, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (backward_button_5), "clicked", G_CALLBACK (backward_cb_5), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_backward_5_cb), data);
  
  /******************forward 5 ************************************/
  
  forward_button_5=gtk_button_new();
  
  GtkBox *forward5_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(forward_button_5), GTK_WIDGET(forward5_button_box));
  
  GtkWidget *forward5_label = gtk_label_new("5+");
  gtk_box_pack_start(forward5_button_box, forward5_label, FALSE, FALSE, 0);
  
  GtkWidget *forward5_icon = gtk_image_new_from_icon_name("pan-end-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(forward5_button_box, forward5_icon, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (forward_button_5), "clicked", G_CALLBACK (forward_cb_5), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_forward_5_cb), data);
  
  
  /*****************************next 10%**************************/
  
  per_forward_button=gtk_button_new();
  
  GtkBox *per_for_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(per_forward_button), GTK_WIDGET(per_for_button_box));
  
  GtkWidget *per_for_label = gtk_label_new("10% +");
  gtk_box_pack_start(per_for_button_box, per_for_label, FALSE, FALSE, 0);
  
  GtkWidget *per_for_icon = gtk_image_new_from_icon_name("go-next-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(per_for_button_box, per_for_icon, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (per_forward_button), "clicked", G_CALLBACK (forward_cb_per), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_forward_per_cb), data);
  
  /*******************************prev 10%***************************************/
  
  per_backward_button=gtk_button_new();
  
  GtkBox *per_back_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(per_backward_button), GTK_WIDGET(per_back_button_box));
  
  GtkWidget *per_back_icon = gtk_image_new_from_icon_name("go-previous-symbolic", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(per_back_button_box, per_back_icon, FALSE, FALSE, 0);

  GtkWidget *per_back_label = gtk_label_new("10% -");
  gtk_box_pack_start(per_back_button_box, per_back_label, FALSE, FALSE, 0);
  g_signal_connect (G_OBJECT (per_backward_button), "clicked", G_CALLBACK (backward_cb_per), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_backward_per_cb), data);
  
  /********************************previous song ************************************/
  
  previous_button = gtk_button_new();
  
  GtkBox *pre_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(previous_button), GTK_WIDGET(pre_button_box));
  
  GtkWidget *pre_icon = gtk_image_new_from_icon_name("media-skip-backward", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(pre_button_box, pre_icon, FALSE, FALSE, 0);

  GtkWidget *pre_label = gtk_label_new("Previous");
  gtk_box_pack_start(pre_button_box, pre_label, FALSE, FALSE, 0);
  g_signal_connect(G_OBJECT(previous_button), "clicked", G_CALLBACK(play_previous_cb), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_prev_cb), data);

  /************************************next song *********************************/
  
  next_button = gtk_button_new();
  
  GtkBox *next_button_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
  gtk_container_add(GTK_CONTAINER(next_button), GTK_WIDGET(next_button_box));

  GtkWidget *next_label = gtk_label_new("Next");
  gtk_box_pack_start(next_button_box, next_label, FALSE, FALSE, 0);
  
  GtkWidget *next_icon = gtk_image_new_from_icon_name("media-skip-forward", GTK_ICON_SIZE_SMALL_TOOLBAR);
  gtk_box_pack_start(next_button_box, next_icon, FALSE, FALSE, 0);
  g_signal_connect(G_OBJECT(next_button), "clicked", G_CALLBACK(play_next_cb), data);
  
  gtk_widget_add_events(main_window, GDK_KEY_PRESS_MASK);
  g_signal_connect(G_OBJECT(main_window), "key-press-event", G_CALLBACK(key_next_cb), data);
  
  /******************start Duration**************************/
    
  start=gtk_button_new();
	GtkBox *start_box=GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
	gtk_container_add(GTK_CONTAINER(start), GTK_WIDGET(start_box));
	data->curr_duration = gtk_label_new("0:00:00");
	gtk_box_pack_start(start_box, data->curr_duration, FALSE, FALSE, 0);
  
  /********************slider*********************************/
  
  data->slider = gtk_scale_new_with_range (GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
  gtk_scale_set_draw_value (GTK_SCALE (data->slider), 0);
  data->slider_update_signal_id = g_signal_connect (G_OBJECT (data->slider), "value-changed", G_CALLBACK (slider_cb), data);
  
  
  /********************* End Duration *****************************/
    
    end=gtk_button_new();
	GtkBox *end_box=GTK_BOX(gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 4));
	gtk_container_add(GTK_CONTAINER(end), GTK_WIDGET(end_box));
	data->end_duration = gtk_label_new("end");
	gtk_box_pack_start(end_box, data->end_duration, FALSE, FALSE, 0);
	
  /****************stream list************************************/

  data->streams_list = gtk_text_view_new ();
  gtk_text_view_set_editable (GTK_TEXT_VIEW (data->streams_list), FALSE);
  gtk_widget_set_can_focus(main_window, TRUE); // Set the window to be focusable
  gtk_widget_grab_focus(main_window); // Grab focus on the window to receive key events

// Create the button and icon for displaying info
  GtkWidget *button1 = gtk_button_new();
  GtkWidget *icon1 = gtk_image_new_from_icon_name("gtk-info", GTK_ICON_SIZE_BUTTON);
  gtk_button_set_image(GTK_BUTTON(button1), icon1);
  // Connect the button to the callback function
  g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), main_window);

  gtk_window_set_title(GTK_WINDOW(main_window), "My Media Player");

  controls = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX (controls), per_backward_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), backward_button_5, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), backward_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), previous_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), playpause_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), stop_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), next_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), forward_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), forward_button_5, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), per_forward_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls), button1, FALSE, FALSE, 2);
  
  controls1 = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX (controls1), visualizer_button, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls1), start, FALSE, FALSE, 2);
  gtk_box_pack_start (GTK_BOX (controls1), data->slider, TRUE, TRUE, 2);
  gtk_box_pack_start (GTK_BOX (controls1), end, FALSE, FALSE, 2);
  
  /**********************volume_box-******************************************/
  GtkWidget *volume_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start (GTK_BOX (volume_box), GTK_WIDGET(data->volume_slider), TRUE, TRUE, 2);
  gtk_box_pack_start (GTK_BOX (volume_box), GTK_WIDGET(icon), FALSE, FALSE, 2);
 
  data->filename_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
  data->filename_label = gtk_label_new(filename);
  gtk_box_pack_start(data->filename_box, data->filename_label, FALSE, FALSE, 0);
  
  data->artist_box = GTK_BOX(gtk_box_new(GTK_ORIENTATION_VERTICAL, 0));
  data->artist_label = gtk_label_new(artist);
  gtk_box_pack_start(data->artist_box, data->artist_label, FALSE, FALSE, 0);
  
  main_hbox = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
  gtk_box_pack_start (GTK_BOX (main_hbox), video_window, TRUE, TRUE, 0);
  gtk_box_pack_start (GTK_BOX (main_hbox), volume_box, FALSE, FALSE, 0);

  main_box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(main_box), GTK_WIDGET(data->filename_box), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX(main_box), GTK_WIDGET(data->artist_box), FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX (main_box), main_hbox, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX (main_box), controls, FALSE, FALSE, 0);
  gtk_box_pack_start(GTK_BOX (main_box), controls1, FALSE, FALSE, 0);
  gtk_container_add(GTK_CONTAINER (main_window), main_box);
  gtk_window_set_default_size (GTK_WINDOW (main_window), 640, 480);
  gtk_widget_show_all (main_window);
}


