#include "header.h"
#include "gui.h"

/* This function is called when the GUI toolkit creates the physical window that will hold the video.
 * At this point we can retrieve its handler (which has a different meaning depending on the windowing system)
 * and pass it to GStreamer through the VideoOverlay interface. */
 void realize_cb (GtkWidget *widget, CustomData *data) {
  GdkWindow *window = gtk_widget_get_window (widget);
  guintptr window_handle;

  if (!gdk_window_ensure_native (window))
  g_error ("Couldn't create native window needed for GstVideoOverlay!");
  

// Retrieve window handler from GDK 
#if defined (GDK_WINDOWING_WIN32)
  window_handle = (guintptr)GDK_WINDOW_HWND (window);
#elif defined (GDK_WINDOWING_QUARTZ)
  window_handle = gdk_quartz_window_get_nsview (window);
#elif defined (GDK_WINDOWING_X11)
  window_handle = GDK_WINDOW_XID (window);
#endif
  // Pass it to playbin, which implements VideoOverlay and will forward it to the video sink 
  gst_video_overlay_set_window_handle (GST_VIDEO_OVERLAY (data->playbin), window_handle);
}

// This function is called periodically to refresh the GUI 
 gboolean refresh_ui (CustomData *data) {
  gint64 current = -1;
  data->duration=-1;

  // We do not want to update anything unless we are in the PAUSED or PLAYING states 
  if (data->state < GST_STATE_PAUSED)
    return TRUE;

  // If we didn't know it yet, query the stream duration 
  if (!GST_CLOCK_TIME_IS_VALID (data->duration)) {
    if (!gst_element_query_duration (data->playbin, GST_FORMAT_TIME, &data->duration)) {
     // g_printerr ("Could not query current duration.\n");
    } else {
      // Set the range of the slider to the clip duration, in SECONDS 
      gtk_range_set_range (GTK_RANGE (data->slider), 0, (gdouble)data->duration / GST_SECOND);
    }
    
    // Fetching the total duration of video and show in UI
      gint dur,second,minute,hour;
      dur = data->duration / GST_SECOND;
			second=dur%60;
			minute=dur/60;
			hour=dur/(60*60);
		
      string str = '0' + to_string(hour) + ":" + '0' + to_string(minute) + ":" + to_string(second);
    	gtk_label_set_label(GTK_LABEL(data->end_duration), str.c_str());
  }

  if (gst_element_query_position (data->playbin, GST_FORMAT_TIME, &current)) {
    /* Block the "value-changed" signal, so the slider_cb function is not called
     * (which would trigger a seek the user has not requested) */
    g_signal_handler_block (data->slider, data->slider_update_signal_id);
    // Set the position of the slider to the current pipeline position, in SECONDS 
    gtk_range_set_value (GTK_RANGE (data->slider), (gdouble)current / GST_SECOND);
    // Re-enable the signal 
    g_signal_handler_unblock (data->slider, data->slider_update_signal_id);
    
    // Fetching the current duration of video and show in UI
    gint dur,second,minute,hour;
    dur = current / GST_SECOND;
		second=dur%60;
		minute=dur/60;
		hour=dur/(60*60);
    
    string str = '0' + to_string(hour) + ":" + '0' + to_string(minute) + ":" + to_string(second);
    gtk_label_set_label(GTK_LABEL(data->curr_duration), str.c_str());
  }
  
  //----filename------------
  
  g_object_get_property(G_OBJECT(data->playbin), "current-uri", &uri);

	// Extract the filename from the URI
	uri_str = g_value_get_string(&uri);
	filename = g_path_get_basename(uri_str);

	// Update the label on the video window
	gchar *label_file = g_strdup_printf("%s", filename);
  gtk_label_set_text(GTK_LABEL(data->filename_label), label_file);
  g_free(label_file);
	g_value_unset(&uri);
  
  // Get the current playing song's metadata 
  if (GST_IS_TAG_LIST(tags)) {
    if (gst_tag_list_get_string(tags, GST_TAG_ARTIST, &artist)) {
     // Update the label on the video window 
      gchar *label_text = g_strdup_printf("%s", artist);
      gtk_label_set_text(GTK_LABEL(data->artist_label), label_text);
      g_free(label_text);
    }
    gst_tag_list_unref(tags);
  }
  return TRUE;
}

void get_Filename(CustomData *data) {
  g_object_get_property(G_OBJECT(data->playbin), "current-uri", &uri);

	// Extract the filename from the URI
	uri_str = g_value_get_string(&uri);
	filename = g_path_get_basename(uri_str);
	g_value_unset(&uri);
}

void get_artist(CustomData *data) {
    artist = NULL;
    while(TRUE) {
      msg = gst_bus_timed_pop_filtered (GST_ELEMENT_BUS (data->playbin),GST_CLOCK_TIME_NONE,(GstMessageType)(GST_MESSAGE_ASYNC_DONE | GST_MESSAGE_TAG | GST_MESSAGE_ERROR));
    	gst_message_parse_tag(msg, &tags);
      gst_tag_list_get_string(tags, GST_TAG_ARTIST, &artist);

    	if(artist != NULL) {
        break;
    	}
   		gst_tag_list_unref(tags);
    }
	  g_print("Artist : %s\n", artist);
}

void visualizer_cb(GtkButton *button,CustomData *data) {

  random_device rd;
  mt19937 rng(rd());
  uniform_int_distribution<int> visDist(0, visualizers.size()-1);
  visualizer = visualizers[visDist(rng)];

    // Set the visualization flag 
    g_object_get (data->playbin, "flags", &flags, NULL);
    flags |= GST_PLAY_FLAG_VIS;
    g_object_set (data->playbin, "flags", flags, NULL);

    // Set the visualizer as the sink for playbin
    GstElement *vis_plugin = gst_element_factory_make(visualizer.c_str(), "visualization");
    if (visualizer == "spacescope") {
    g_object_set(vis_plugin, "shade-amount", "rainbow", "style", 3, NULL);
    g_object_set(vis_plugin, "shader", 9, NULL);
    } else if (visualizer == "goom" || visualizer == "goom2k1" || visualizer == "Oscilloscope") {
    g_object_set(vis_plugin, "shader", 5, NULL);
    } else if (visualizer == "spectrascope") {
    g_object_set(vis_plugin, "shade-amount", "Coolwarm", "shader", 3, NULL);
    } else if (visualizer == "synaescope") {
    g_object_set(vis_plugin, "shader", 9, NULL);
    } else if (visualizer == "wavescope") {
    g_object_set(vis_plugin, "shader", 4, "shade-amount", "Viridis", NULL);
    }
    g_object_set(data->playbin, "vis-plugin", vis_plugin, NULL);
}

void play_pause(GtkButton *button,CustomData *data) {
    GstState state;
    gst_element_get_state(data->playbin,&state, NULL, GST_CLOCK_TIME_NONE);
    if(state==GST_STATE_PLAYING)
    {
      gst_element_set_state(data->playbin,GST_STATE_PAUSED);
    }
    else
    {
     	gst_element_set_state(data->playbin,GST_STATE_PLAYING);
     	 
     	/* Set the visualization flag */
      g_object_get (data->playbin, "flags", &flags, NULL);
      flags |= GST_PLAY_FLAG_VIS;
      g_object_set (data->playbin, "flags", flags, NULL);
     }
}


/* This function is called when the STOP button is clicked */
void stop_cb (GtkButton *button, CustomData *data) {
  gst_element_set_state (data->playbin, GST_STATE_READY);
  play_pause(NULL,data);
}

/* This function is called when the main window is closed */
void delete_event_cb (GtkWidget *widget, GdkEvent *event, CustomData *data) {
  stop_cb (NULL, data);
  gtk_main_quit ();
}

/* This function is called when the VOLUME UP button is clicked */
void volume_up_cb (GtkButton *button, CustomData *data) {
  gdouble volume;
  g_object_get (data->playbin, "volume", &volume, NULL);
  volume += 0.1;
  if (volume > 1.0)
    volume = 1.0;
  g_object_set (data->playbin, "volume", volume, NULL);
}

/* This function is called when the VOLUME DOWN button is clicked */
void volume_down_cb (GtkButton *button, CustomData *data) {
  gdouble volume;
  g_object_get (data->playbin, "volume", &volume, NULL);
  volume -= 0.1;
  if (volume < 0.0)
    volume = 0.0;
  g_object_set (data->playbin, "volume", volume, NULL);
}

//This is the function to navigate to the previous song
void play_previous_song(int* current_song_index, GstElement* playbin,CustomData *data) {
    gst_element_set_state(playbin, GST_STATE_NULL);
    (*current_song_index)--;
    if (*current_song_index < 0) {
        *current_song_index = media_files.size() - 1;
    }
    //g_print("song index: %d\n",&current_song_index);
    g_object_set(G_OBJECT(playbin), "uri", g_filename_to_uri(media_files[*current_song_index], NULL, NULL), NULL);
    gst_element_set_state(playbin, GST_STATE_PLAYING);
    get_artist(data);
    get_Filename(data);
}

// Callback function for the "Previous" button
void play_previous_cb(GtkButton *button, CustomData *data,std::vector<gchar*>& media_files)
{
    g_print("previous button clicked\n");
    play_previous_song(&current_song_index, data->playbin, data);
}

//This is the function to navigate to the next song
 void play_next_song(int* current_song_index, GstElement* playbin, CustomData *data) {
    gst_element_set_state(playbin, GST_STATE_NULL);
    (*current_song_index)++;
    if (*current_song_index >= media_files.size()) {
        *current_song_index = 0;
    }
    g_object_set(G_OBJECT(playbin), "uri", g_filename_to_uri(media_files[*current_song_index], NULL, NULL), NULL);
    gst_element_set_state(playbin, GST_STATE_PLAYING);
    get_artist(data);
    get_Filename(data);
}

// Callback function for the "Next" button
void play_next_cb(GtkButton *button, CustomData *data,std::vector<gchar*>& media_files) {
     
     play_next_song(&current_song_index, data->playbin,data);
}

/* Callback function for the forward button */
  void forward_cb(GtkButton *button, CustomData *data) {
  gint64 current_position;
  gint64 new_position;

  /* Get the current position of the pipeline */
  gst_element_query_position(data->playbin, GST_FORMAT_TIME, &current_position);

  /* Calculate the new position by adding 60 seconds */
  new_position = current_position + GST_SECOND * 60;

  /* Seek to the new position */
  gst_element_seek_simple(data->playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, new_position);
}


/* Callback function for the backward button */
 void backward_cb(GtkButton *button, CustomData *data) {
  gint64 current_position;
  gint64 new_position;

  /* Get the current position of the pipeline */
  gst_element_query_position(data->playbin, GST_FORMAT_TIME, &current_position);

  /* Calculate the new position by subtracting 60 seconds */
  new_position = current_position - GST_SECOND * 60;

  /* Seek to the new position */
  gst_element_seek_simple(data->playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, new_position);
}


/* Callback function for the forward button */
 void forward_cb_5(GtkButton *button, CustomData *data) {
  gint64 current_position;
  gint64 new_position;

  /* Get the current position of the pipeline */
  gst_element_query_position(data->playbin, GST_FORMAT_TIME, &current_position);

  /* Calculate the new position by adding 60 seconds */
  new_position = current_position + GST_SECOND * 5;

  /* Seek to the new position */
  gst_element_seek_simple(data->playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, new_position);
}

/* Callback function for the backward button */
 void backward_cb_5(GtkButton *button, CustomData *data) {
  gint64 current_position;
  gint64 new_position;

  /* Get the current position of the pipeline */
  gst_element_query_position(data->playbin, GST_FORMAT_TIME, &current_position);

  /* Calculate the new position by subtracting 60 seconds */
  new_position = current_position - GST_SECOND * 5;

  /* Seek to the new position */
  gst_element_seek_simple(data->playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, new_position);
}

/*callback function for the forward button for 10%*/
    void forward_cb_per(GtkButton *button, CustomData *data) {
    gint64 total_duration;
    gint64 current_position;
    
    /*Get the total duration of the pipeline*/
    gst_element_query_duration(data->playbin, GST_FORMAT_TIME, &total_duration);
    
    /*Get the current position for the pipeline*/
    gst_element_query_position(data->playbin, GST_FORMAT_TIME, &current_position);
    
    /*Calculate new position*/
    gint64 new_position = current_position + (total_duration / 10);
    
    /*seek to the new position*/
    gst_element_seek_simple(data->playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, new_position);
}

/*callback function for the backward button for 10%*/
    void backward_cb_per(GtkButton *button, CustomData *data) {
    gint64 total_duration;
    gint64 current_position;
    
    /*Get the total duration of the pipeline*/
    gst_element_query_duration(data->playbin, GST_FORMAT_TIME, &total_duration);
    
    /*Get the current position for the pipeline*/
    gst_element_query_position(data->playbin, GST_FORMAT_TIME, &current_position);
    
    /*Calculate new position*/
    gint64 new_position = current_position - (total_duration / 10);
    
    /*seek to the new position*/
    gst_element_seek_simple(data->playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, new_position);
}
//Info about APP_NAME and VISUALIZER
gboolean on_button_clicked(GtkWidget *widget, gpointer data) {
  GtkWindow *parent_window = GTK_WINDOW(data);
  GtkWidget *dialog = gtk_message_dialog_new(parent_window,
                                             GTK_DIALOG_MODAL,
                                             GTK_MESSAGE_INFO,
                                             GTK_BUTTONS_OK,
                                             "App Name and Version");
  gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(dialog),
                                           "%s - %s\n\n"
                                           "Developed by:\n"
                                           "Dharani S\n"
                                           "Geethanjali Patil\n"
                                           "Kavya Naik\n"
                                           "Megha L\n"
                                           "Ramyashree M\n"
                                           "Pooja Baadkar\n"
                                           "Adarsha N Y\n"
                                           "Saurabh Patel\n",
                                            APP_NAME, APP_VERSION);
  gtk_dialog_run(GTK_DIALOG(dialog));
  gtk_widget_destroy(dialog);
  return 0;
}

/* This function is called everytime the video window needs to be redrawn (due to damage/exposure,
 *rescaling, etc). GStreamer takes care of this in the PAUSED and PLAYING states, otherwise,
 * we simply draw a black rectangle to avoid garbage showing up. */
 gboolean draw_cb (GtkWidget *widget, cairo_t *cr, CustomData *data) {
  if (data->state < GST_STATE_PAUSED) {
    GtkAllocation allocation;

    /* Cairo is a 2D graphics library which we use here to clean the video window.
     * It is used by GStreamer for other reasons, so it will always be available to us. */
    gtk_widget_get_allocation (widget, &allocation);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_rectangle (cr, 0, 0, allocation.width, allocation.height);
    cairo_fill (cr);
  }

  return FALSE;
}

/* This function is called when the slider changes its position. We perform a seek to the
 * new position here. */
 void slider_cb (GtkRange *range, CustomData *data) {
  gdouble value = gtk_range_get_value (GTK_RANGE (data->slider));
  gst_element_seek_simple (data->playbin, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH,
      (gint64)(value * GST_SECOND));
}

//setting volume 
 void set_volume(GstElement *playbin, double volume) {
  if (playbin != NULL) {
    g_object_set (playbin, "volume", volume, NULL);
  }
}

//fetching the volume range
 void volume_slider_cb (GtkRange *range, CustomData *data) {
  gdouble value = gtk_range_get_value (GTK_RANGE (data->volume_slider));
  set_volume(data->playbin, value);
}

/* This function is called when new metadata is discovered in the stream */
 void tags_cb (GstElement *playbin, gint stream, CustomData *data) {
  /* We are possibly in a GStreamer working thread, so we notify the main
   * thread of this event through a message in the bus */
  gst_element_post_message (playbin,
    gst_message_new_application (GST_OBJECT (playbin),
      gst_structure_new_empty ("tags-changed")));
}

/* This function is called when an error message is posted on the bus */
 void error_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
  GError *err;
  gchar *debug_info;

  /* Print error details on the screen */
  gst_message_parse_error (msg, &err, &debug_info);
  g_printerr ("Error received from element %s: %s\n", GST_OBJECT_NAME (msg->src), err->message);
  g_printerr ("Debugging information: %s\n", debug_info ? debug_info : "none");
  g_clear_error (&err);
  g_free (debug_info);

  /* Set the pipeline to READY (which stops playback) */
  gst_element_set_state (data->playbin, GST_STATE_READY);
}

/* This function is called when an End-Of-Stream message is posted on the bus.
 * We just set the pipeline to READY (which stops playback) */
 void eos_cb (GstBus *bus, GstMessage *msg, CustomData *data,GstElement* playbin,std::vector<gchar*>& media_files) {
  g_print ("End-Of-Stream reached.\n");
   play_next_song(&current_song_index, data->playbin,data);

}

/* This function is called when the pipeline changes states. We use it to
 * keep track of the current state. */
 void state_changed_cb (GstBus *bus, GstMessage *msg, CustomData *data) {
  GstState old_state, new_state, pending_state;
  gst_message_parse_state_changed (msg, &old_state, &new_state, &pending_state);
  if (GST_MESSAGE_SRC (msg) == GST_OBJECT (data->playbin)) {
    data->state = new_state;
    g_print ("State set to %s\n", gst_element_state_get_name (new_state));
    if (old_state == GST_STATE_READY && new_state == GST_STATE_PAUSED) {
      /* For extra responsiveness, we refresh the GUI as soon as we reach the PAUSED state */
      refresh_ui (data);
    }
  }
}

