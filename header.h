#include<iostream>
#include <string.h>
#include <random>
#include <gtk/gtk.h>
#include <gst/gst.h>
#include <gst/video/videooverlay.h>

#include <gdk/gdk.h>
#if defined (GDK_WINDOWING_X11)
#include <gdk/gdkx.h>
#elif defined (GDK_WINDOWING_WIN32)
#include <gdk/gdkwin32.h>
#elif defined (GDK_WINDOWING_QUARTZ)
#include <gdk/gdkquartz.h>
#endif

#include<dirent.h>
#include <vector>
#include<gst/tag/tag.h>

#define FOLDER "/home/ee213017/eclipse-workspace/audio"

#define APP_NAME "JUKE-GENIE PLAYER"
#define APP_VERSION "1.0.0"
 
using namespace std;

// Global variables
vector<gchar*> media_files;
vector<string> visualizers ;
gchar *artist;
GstMessage *msg;
GstBus *bus;
guint flags;
string visualizer;
GstTagList *tags = NULL;
GValue uri = G_VALUE_INIT;
const gchar* uri_str;
gchar *filename;
static int current_song_index = 0;


//playbin flags 
typedef enum {
  GST_PLAY_FLAG_VIS           = (1 << 3) // Enable rendering of visualizations when there is no video stream.
} GstPlayFlags;


vector<string> getVisualizers() {
    // TODO: implement function to get available visualizers
	    vector<string> visualizers = {"goom", "monoscope", "wavescope", "spectrascope", "synaescope", "goom2k1"};
	    return visualizers;
}
 

// Structure to contain all our information, so we can pass it around 
typedef struct _CustomData {
  GstElement *playbin,*vis_plugin=NULL;           //Our one and only pipeline 

  GtkWidget *slider, *volume_slider;              //Slider widget to keep track of current position 
  GtkWidget *streams_list; 
  GtkBox *filename_box;
  GtkBox *artist_box;
  GtkWidget *filename_label;
  GtkWidget *artist_label;                        //Text widget to display info about the streams 
  gulong slider_update_signal_id;                 // Signal ID for the slider update signal 

  GtkWidget *end_duration;
  GtkWidget *curr_duration;
  GstState state;                                //  Current state of the pipeline 
  gint64 duration;                               // Duration of the clip, in nanoseconds
  gboolean playing;
  gchar *current_file;  
} CustomData;

CustomData data;





















































