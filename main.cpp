#include <gtk/gtk.h>

// Callback for navigation buttons to switch pages
static void on_button_clicked(GtkWidget *button, gpointer data) {
    GtkStack *stack = GTK_STACK(data); // Cast gpointer to GtkStack*
    const char *page_name = gtk_widget_get_name(button); // Get the button's name
    gtk_stack_set_visible_child_name(stack, page_name); // Switch to the page with this name
}

// Callback for login button
static void on_login_clicked(GtkWidget *button, gpointer data) {
    GtkWidget **entries = (GtkWidget **)data; // Cast the gpointer to GtkWidget** to access entries
    GtkEntry *username_entry = GTK_ENTRY(entries[0]); // First entry is the username
    GtkEntry *password_entry = GTK_ENTRY(entries[1]); // Second entry is the password
    GtkStack *stack = GTK_STACK(entries[2]); // Third element is the stack
    GtkWidget *nav_container = entries[3]; // Fourth element is the navigation container

    const char *username = gtk_entry_get_text(username_entry);
    const char *password = gtk_entry_get_text(password_entry);

    // Validate username and password (hardcoded values here)
    if (g_strcmp0(username, "admin") == 0 && g_strcmp0(password, "password") == 0) {
        g_print("Login successful! Username: %s\n", username);
        gtk_stack_set_visible_child_name(stack, "Profile"); // Show the initial main page
        gtk_widget_show(nav_container); // Make the navigation buttons visible
    } else {
        g_print("Invalid login credentials!\n");
    }
}

int main(int argc, char *argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK Application with Hidden Navigation");
    gtk_window_set_default_size(GTK_WINDOW(window), 1280, 720);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box to hold the entire layout
    GtkWidget *main_vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), main_vbox);

    // --- STACK FOR PAGES ---
    GtkWidget *stack = gtk_stack_new();
    gtk_box_pack_start(GTK_BOX(main_vbox), stack, TRUE, TRUE, 0);

    // --- LOGIN PAGE ---
    GtkWidget *login_page = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_stack_add_named(GTK_STACK(stack), login_page, "Login");

    GtkWidget *username_label = gtk_label_new("Username:");
    gtk_box_pack_start(GTK_BOX(login_page), username_label, FALSE, FALSE, 0);

    GtkWidget *username_entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(login_page), username_entry, FALSE, FALSE, 0);

    GtkWidget *password_label = gtk_label_new("Password:");
    gtk_box_pack_start(GTK_BOX(login_page), password_label, FALSE, FALSE, 0);

    GtkWidget *password_entry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(password_entry), FALSE); // Hide password characters
    gtk_box_pack_start(GTK_BOX(login_page), password_entry, FALSE, FALSE, 0);

    GtkWidget *login_button = gtk_button_new_with_label("Login");

    // Navigation container (initially hidden)
    GtkWidget *nav_hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_widget_hide(nav_hbox); // Initially hide the navigation buttons
    gtk_box_pack_end(GTK_BOX(main_vbox), nav_hbox, FALSE, TRUE, 0);

    // Pass entries, stack, and nav_hbox to the login callback
    GtkWidget *callback_data[] = { username_entry, password_entry, stack, nav_hbox };
    g_signal_connect(login_button, "clicked", G_CALLBACK(on_login_clicked), callback_data);
    gtk_box_pack_start(GTK_BOX(login_page), login_button, FALSE, FALSE, 0);

    // --- MAIN APPLICATION PAGES ---
    GtkWidget *page1 = gtk_label_new("This is the Profile page.");
    gtk_stack_add_named(GTK_STACK(stack), page1, "Profile");

    GtkWidget *page2 = gtk_label_new("This is the News page.");
    gtk_stack_add_named(GTK_STACK(stack), page2, "News");

    GtkWidget *page3 = gtk_label_new("This is the Messenger page.");
    gtk_stack_add_named(GTK_STACK(stack), page3, "Messenger");

    GtkWidget *page4 = gtk_label_new("This is the Settings page.");
    gtk_stack_add_named(GTK_STACK(stack), page4, "Settings");

    GtkWidget *page5 = gtk_label_new("This is the About page.");
    gtk_stack_add_named(GTK_STACK(stack), page5, "About");

    // --- NAVIGATION BUTTONS ---
    GtkWidget *button1 = gtk_button_new_with_label("Profile");
    gtk_widget_set_name(button1, "Profile");
    g_signal_connect(button1, "clicked", G_CALLBACK(on_button_clicked), stack);
    gtk_box_pack_start(GTK_BOX(nav_hbox), button1, TRUE, TRUE, 0);

    GtkWidget *button2 = gtk_button_new_with_label("News");
    gtk_widget_set_name(button2, "News");
    g_signal_connect(button2, "clicked", G_CALLBACK(on_button_clicked), stack);
    gtk_box_pack_start(GTK_BOX(nav_hbox), button2, TRUE, TRUE, 0);

    GtkWidget *button3 = gtk_button_new_with_label("Messenger");
    gtk_widget_set_name(button3, "Messenger");
    g_signal_connect(button3, "clicked", G_CALLBACK(on_button_clicked), stack);
    gtk_box_pack_start(GTK_BOX(nav_hbox), button3, TRUE, TRUE, 0);

    GtkWidget *button4 = gtk_button_new_with_label("Settings");
    gtk_widget_set_name(button4, "Settings");
    g_signal_connect(button4, "clicked", G_CALLBACK(on_button_clicked), stack);
    gtk_box_pack_start(GTK_BOX(nav_hbox), button4, TRUE, TRUE, 0);

    GtkWidget *button5 = gtk_button_new_with_label("About");
    gtk_widget_set_name(button5, "About");
    g_signal_connect(button5, "clicked", G_CALLBACK(on_button_clicked), stack);
    gtk_box_pack_start(GTK_BOX(nav_hbox), button5, TRUE, TRUE, 0);

    // Show the main window and ensure the login page is displayed
    gtk_widget_show_all(window);
    gtk_widget_hide(nav_hbox); // Ensure the navigation buttons remain hidden

    // Run the GTK main loop
    gtk_main();

    return 0;
}
