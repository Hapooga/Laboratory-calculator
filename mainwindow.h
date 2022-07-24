#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE

namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

//-------------// Event Filter Method //------------------------

    bool eventFilter(QObject *watched, QEvent *event);

//-------------// DB Functions //------------------------

    bool add_new_db_data(const QString& acid_limit_input, const QString& equivalent_limit);

    bool delete_db_data (const QString& acid_limit_input);

    void reload_db_output();

    void on_db_add_data_input_Button_clicked();

    void on_db_delete_data_Button_clicked();

    void on_db_exit_admin_Button_clicked();

//-------------// Change Menu Methods //------------------------

    void on_molar_solutions_menubur_triggered();

    void on_normal_concentration_menubur_triggered();

    void on_ligation_menubur_triggered();

//-------------// Normal Concentration Check Boxes //-------------

    void on_normal_concentration_concentration_radioButton_clicked();

    void on_normal_concentration_volume_radioButton_clicked();

    void on_normal_concentration_mass_radioButton_clicked();

//-------------// Molar Solutions Check Boxes //-------------

    void on_molar_solutions_volume_radioButton_clicked();

    void on_molar_solutions_molar_concentration_radioButton_clicked();

    void on_molar_solutions_mass_radioButton_clicked();

//-------------// Calculate Methods //------------------------

//-------------// Calculate Molar Solutions //------------------------

    void calculate_molar_solutions_volume();

    void calculate_molar_solutions_molar_concentration();

    void calculate_molar_solutions_mass();

//-------------// Calculate Normal Concentration //------------------------

    void calculate_normal_concentration_volume();

    void calculate_normal_concentration_concentration();

    void calculate_normal_concentration_mass();

//-------------// Calculate Ligation //------------------------

    void calculate_ligation();

    void on_calculate_Button_clicked();

    void on_clear_Button_clicked();

private:

    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
