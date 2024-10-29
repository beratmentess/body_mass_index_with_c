#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

GtkWidget *entry_name;
GtkWidget *entry_surname;
GtkWidget *entry_birthdate;
GtkWidget *entry_weight;
GtkWidget *entry_height;
GtkWidget *label_result;

int calculate_age(const char *birthdate) {
    struct tm birth_tm = {0};
    sscanf(birthdate, "%d-%d-%d", &birth_tm.tm_year, &birth_tm.tm_mon, &birth_tm.tm_mday);
    birth_tm.tm_year -= 1900; // Yıl 1900'den itibaren sayılıyor
    birth_tm.tm_mon -= 1; // Ay 0'dan başlıyor

    time_t now = time(NULL);
    struct tm *now_tm = localtime(&now);

    int age = now_tm->tm_year - birth_tm.tm_year;
    if (now_tm->tm_mon < birth_tm.tm_mon ||
        (now_tm->tm_mon == birth_tm.tm_mon && now_tm->tm_mday < birth_tm.tm_mday)) {
        age--;
    }
    return age;
}

void calculate_bmi(GtkWidget *widget, gpointer data) {
    const char *name = gtk_entry_get_text(GTK_ENTRY(entry_name));
    const char *surname = gtk_entry_get_text(GTK_ENTRY(entry_surname));
    const char *birthdate = gtk_entry_get_text(GTK_ENTRY(entry_birthdate));
    float weight = atof(gtk_entry_get_text(GTK_ENTRY(entry_weight)));
    float height = atof(gtk_entry_get_text(GTK_ENTRY(entry_height))) / 100.0;

    // Yaş hesaplama
    int age = calculate_age(birthdate);

    // BMI Hesaplama
    float bmi = weight / (height * height);
    char *bmi_category;

    if (bmi < 18.5) {
        bmi_category = "Zayıf";
    } else if (bmi < 24.9) {
        bmi_category = "Normal";
    } else if (bmi < 29.9) {
        bmi_category = "Kilolu";
    } else if (bmi < 34.9) {
        bmi_category = "Fazla Kilolu";
    } else {
        bmi_category = "Obez";
    }

    // Sonucu oluşturma
    char result[256];
    snprintf(result, sizeof(result), "Ad Soyad: %s %s \nYaş: %d \nVücut Kitle İndeksi: %.2f (%s)",
             name, surname, age, bmi, bmi_category);

    gtk_label_set_text(GTK_LABEL(label_result), result);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Vücut Kitle İndeksi Hesaplayıcı");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    entry_name = gtk_entry_new();
    entry_surname = gtk_entry_new();
    entry_birthdate = gtk_entry_new();
    entry_weight = gtk_entry_new();
    entry_height = gtk_entry_new();
    label_result = gtk_label_new("");

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Ad:"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_name, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Soyad:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_surname, 1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Doğum Tarihi (YYYY-MM-DD):"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_birthdate, 1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Kilo (kg):"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_weight, 1, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Boy (cm):"), 0, 4, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_height, 1, 4, 1, 1);

    GtkWidget *button_calculate = gtk_button_new_with_label("Hesapla");
    g_signal_connect(button_calculate, "clicked", G_CALLBACK(calculate_bmi), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_calculate, 0, 5, 2, 1);

    gtk_grid_attach(GTK_GRID(grid), label_result, 0, 6, 2, 1);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
