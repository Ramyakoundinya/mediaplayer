#include "header.h"
#include "gui.h"
#include "keyboard.h"
#include "buttons.h"

int main(int argc, char *argv[]) {

  DIR *dir;
  CustomData data;
  struct dirent *entry;
    
  GstStateChangeReturn ret;
    
  data.playing = FALSE;
    
  /* Initialize GTK */
  gtk_init (&argc, &argv);

  /* Initialize GStreamer */
  gst_init (&argc, &argv);
    
  /* Initialize our data structure */
  memset (&data, 0, sizeof (data));
  data.duration = GST_CLOCK_TIME_NONE;

  /* Create the elements */
  data.playbin = gst_element_factory_make ("playbin", "playbin");

  if (!data.playbin)
  {
    g_printerr ("Not all elements could be created.\n");
    return -1;
  }

  //open the directory
  dir = opendir(FOLDER);

  if (dir == NULL) 
  {
     g_printerr("Could not open the directory. Exiting.\n");
     return -1;
  }

  //Read the contents of the directory 
  while((entry= readdir(dir))!=NULL)
  {
    if(entry->d_type== DT_REG && (strstr(entry->d_name,".mp3")!=NULL || strstr(entry->d_name,".mp4")!=NULL || strstr(entry->d_name,".webm")!=NULL || strstr(entry->d_name,".avi")!=NULL || strstr(entry->d_name,".flac")!=NULL || strstr(entry->d_name,".wma")!=NULL || strstr(entry->d_name,".ogg")!=NULL) )
    {
      gchar *full_path = g_strdup_printf("%s/%s",FOLDER,entry->d_name);
      media_files.push_back(full_path);
    }
  }
  
  current_song_index = 0; // start with the first song in the list
  
  //set up signal connections for signals emitted by the playbin element
  g_signal_connect (G_OBJECT (data.playbin), "video-tags-changed", (GCallback) tags_cb, &data);
  g_signal_connect (G_OBJECT (data.playbin), "audio-tags-changed", (GCallback) tags_cb, &data);
  g_signal_connect (G_OBJECT (data.playbin), "text-tags-changed", (GCallback) tags_cb, &data);

  //set up signal connections for the bus of a GStreamer pipeline,to monitor messages sent by the pipeline
  bus = gst_element_get_bus (data.playbin);
  gst_bus_add_signal_watch (bus);
  g_signal_connect (G_OBJECT (bus), "message::error", (GCallback)error_cb, &data);
  g_signal_connect(G_OBJECT(bus), "message::eos",reinterpret_cast<GCallback>(eos_cb), &data);
  g_signal_connect (G_OBJECT (bus), "message::state-changed", (GCallback)state_changed_cb, &data);
  
  //---visualizer--------------------
  
  // Get available visualizers
  visualizers = getVisualizers();

  random_device rd;
  mt19937 rng(rd());
  uniform_int_distribution<int> visDist(0, visualizers.size()-1);
  visualizer = visualizers[visDist(rng)];

  /* Start playing the first song */
 	g_object_set(G_OBJECT(data.playbin),"uri",g_filename_to_uri(media_files[current_song_index],NULL,NULL),NULL);

  /* Set the visualization flag */
	g_object_get (data.playbin, "flags", &flags, NULL);
	flags |= GST_PLAY_FLAG_VIS;
	g_object_set (data.playbin, "flags", flags, NULL);

	/* set vis plugin for playbin */
	g_object_set (data.playbin, "vis-plugin", data.vis_plugin, NULL);
	
  ret = gst_element_set_state (data.playbin, GST_STATE_PLAYING);

  //get a filename ----------------
  	
  g_object_get_property(G_OBJECT(data.playbin), "current-uri", &uri);

	// Extract the filename from the URI
	uri_str = g_value_get_string(&uri);
	filename = g_path_get_basename(uri_str);
	cout<<"title:"<<filename;
	g_value_unset(&uri);

	//get artist name using tags-------------------
  	
  while(TRUE)
	{
    msg = gst_bus_timed_pop_filtered (GST_ELEMENT_BUS (data.playbin),GST_CLOCK_TIME_NONE,(GstMessageType)(GST_MESSAGE_ASYNC_DONE | GST_MESSAGE_TAG | GST_MESSAGE_ERROR));
    gst_message_parse_tag(msg, &tags);
    		
    gst_tag_list_get_string(tags, GST_TAG_ARTIST, &artist);
    		
    if(artist != NULL)
    {
      break;
    }
   	gst_tag_list_unref(tags);
	}

  //check whether the state change was successful or not.	
  if (ret == GST_STATE_CHANGE_FAILURE) 
  {
    g_printerr ("Unable to set the pipeline to the playing state.\n");
    return -1; 
  }
    	
  /* Create the GUI */
  create_ui(&data);
  	
  /* Register a function that GLib will call every second */
  g_timeout_add_seconds (1, (GSourceFunc)refresh_ui, &data);

  /* Start the GTK main loop. We will not regain control until gtk_main_quit is called. */
  gtk_main ();

  /* Free resources */
  gst_element_set_state (data.playbin, GST_STATE_NULL);
  gst_object_unref (data.playbin);
  //gst_deinit();
  
  return 0;

}

