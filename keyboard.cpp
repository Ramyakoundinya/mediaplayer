#include "header.h"
#include "gui.h"
#include "keyboard.h"


//This function is called when a key for play_pause is pressed 
gboolean key_play_pause_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
    if (event->keyval == GDK_KEY_space) { // Also we can use ASCII value for 'space' 32
    	play_pause(NULL, data); // call play_pause_cb with NULL button arguement
       	return TRUE;
    }
    return FALSE;
} 


//This function is called when a key for stop is pressed 
gboolean key_stop_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
    if (event->keyval == GDK_KEY_BackSpace) { // Also we can use ASCII value for 'BackSpace' 65288.
    	stop_cb(NULL, data); // call stop_cb with NULL button arguement
       	return TRUE;
    }
    return FALSE;
}


//This function is called when a key for volume up is pressed 
gboolean key_volume_up_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) {
    if (event->keyval == GDK_KEY_plus || event->keyval == GDK_KEY_KP_Add) { //Also we can use ASCII value for '+' 43
        volume_up_cb(NULL, data); // Call volume_up_cb with NULL button argument
        return TRUE;
    }
    return FALSE;
}


//This function is called when a key for volume up is pressed 
gboolean key_volume_down_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) {
    if (event->keyval == GDK_KEY_minus || event->keyval == GDK_KEY_KP_Subtract) { //Also we can use ASCII value for '-' 45
    	volume_down_cb(NULL, data); // Call volume down with NULL button argument
        return TRUE;
    }
    return FALSE;
}


//This function is called when a key for previous song button is pressed 
gboolean key_prev_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
    if (event->keyval == GDK_KEY_less) {
       	play_previous_song(&current_song_index, data->playbin, data); // call play_previous_song function
       	return TRUE;
    }
    return FALSE;
} 


// This function is called when a key for nxt song button is pressed 
gboolean key_next_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
    if (event->keyval == GDK_KEY_greater) {
        play_next_song(&current_song_index, data->playbin,data); // call play_next_song function
       	return TRUE;
    }
    return FALSE;
}  


// This function is called when a key for 5sec forward button is pressed 
gboolean key_forward_5_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
    if (event->keyval == GDK_KEY_Up) {
       	forward_cb_5(NULL, data); // call forward_cb_5 function
       	return TRUE;
    }
    return FALSE;
} 


// This function is called when a key for 5sec backward button is pressed 
gboolean key_backward_5_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
	if (event->keyval == GDK_KEY_Down) {
       	backward_cb_5(NULL, data); // call backward_cb_5 function
       	return TRUE;
    }
    return FALSE;
}  


// This function is called when a key for 60sec forward button is pressed 
gboolean key_forward_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
	if (event->keyval == GDK_KEY_Right) {
       	forward_cb(NULL, data); // call forward_cb function
       	return TRUE;
    }
    return FALSE;
}  


// This function is called when a key for 60sec backward button is pressed 
gboolean key_backward_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
	if (event->keyval == GDK_KEY_Left) {
       	backward_cb(NULL, data); // call backward_cb function
       	return TRUE;
    }
    return FALSE;
}  


// This function is called when a key for 10per forward button is pressed 
gboolean key_forward_per_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
	if (event->keyval == GDK_KEY_braceleft) {
        forward_cb_per(NULL, data); // call forward_cb_per function
       	return TRUE;
    }
    return FALSE;
} 


// This function is called when a key for 10per backward button is pressed 
gboolean key_backward_per_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data) { 
	if (event->keyval == GDK_KEY_braceright) {
       	backward_cb_per(NULL, data); // call backward_cb function
       	return TRUE;
    }
    return FALSE;
}

