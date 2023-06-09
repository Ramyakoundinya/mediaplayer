void realize_cb (GtkWidget *widget, CustomData *data);

gboolean refresh_ui (CustomData *data);

void get_Filename(CustomData *data);

void get_artist(CustomData *data);

void visualizer_cb(GtkButton *button,CustomData *data);

void play_pause(GtkButton *button,CustomData *data);

void stop_cb (GtkButton *button, CustomData *data);

void delete_event_cb (GtkWidget *widget, GdkEvent *event, CustomData *data);

void volume_up_cb (GtkButton *button, CustomData *data);

void volume_down_cb (GtkButton *button, CustomData *data);

void play_previous_song(int* current_song_index, GstElement* playbin,CustomData *data);

void play_previous_cb(GtkButton *button, CustomData *data,std::vector<gchar*>& audio_files);

void play_next_song(int* current_song_index, GstElement* playbin, CustomData *data);

void play_next_cb(GtkButton *button, CustomData *data,std::vector<gchar*>& audio_files);

void forward_cb(GtkButton *button, CustomData *data);

void backward_cb(GtkButton *button, CustomData *data);

void forward_cb_5(GtkButton *button, CustomData *data);

void backward_cb_5(GtkButton *button, CustomData *data);

void forward_cb_per(GtkButton *button, CustomData *data);

void backward_cb_per(GtkButton *button, CustomData *data);

gboolean draw_cb (GtkWidget *widget, cairo_t *cr, CustomData *data);

void slider_cb (GtkRange *range, CustomData *data);

void volume_slider_cb (GtkRange *range, CustomData *data);

void tags_cb (GstElement *playbin, gint stream, CustomData *data);

void error_cb (GstBus *bus, GstMessage *msg, CustomData *data);

void eos_cb (GstBus *bus, GstMessage *msg, CustomData *data,GstElement* playbin,std::vector<gchar*>& audio_files);

void state_changed_cb (GstBus *bus, GstMessage *msg, CustomData *data);

void analyze_streams (CustomData *data);

gboolean on_button_clicked(GtkWidget *widget, gpointer data) ;

void application_cb (GstBus *bus, GstMessage *msg, CustomData *data);

