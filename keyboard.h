 gboolean key_play_pause_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_stop_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_volume_up_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_volume_down_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_prev_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_next_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_forward_5_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_backward_5_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_forward_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_backward_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_forward_per_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 gboolean key_backward_per_cb(GtkWidget *widget, GdkEventKey *event, CustomData *data);

 void play_pause(GtkButton *button,CustomData *data);
