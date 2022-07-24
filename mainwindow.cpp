#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "db_worker.h"
#include "check_functions.h"
#include "formula_parser.h"
#include "residue_finder.h"
#include "calculate.h"

#include <QMessageBox>
#include <QString>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->AdminGroupBox->hide();
    ui->ligation_groupBox->hide();
    ui->normal_concentration_groupBox->hide();
    ui->molar_solutions_volume_radioButton->click();
    ui->normal_concentration_concentration_radioButton->click();
    qApp->installEventFilter(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


//===============================// Event Filter Method //=======================

bool MainWindow::eventFilter(QObject *watched, QEvent *event){

    if(event->type() == QEvent::KeyPress){

        QKeyEvent *key_event = static_cast<QKeyEvent *>(event);

        if(key_event->key() == Qt::Key_Return && ui->WorkGroupBox->isVisible()){

            on_calculate_Button_clicked();

        }
        else if(key_event->key() == Qt::Key_Return && ui->AdminGroupBox->isVisible()){

            on_db_add_data_input_Button_clicked();

        }
        else if(watched == ui->calculate_Button){

            if(key_event->key() == Qt::Key_Control){

                ui->AdminGroupBox->show();
                ui->WorkGroupBox->hide();

                ui->ligation_groupBox->hide();
                ui->normal_concentration_groupBox->hide();

                ui->molar_solutions_menubur->setEnabled(false);
                ui->normal_concentration_menubur->setEnabled(false);
                ui->ligation_menubur->setEnabled(false);

                ui->AdminGroupBox->move(0,0);
                ui->WorkGroupBox->move(0, 380);

                reload_db_output();

            }
        }

    }

    QObject::eventFilter(watched,event);

    return false;
}

//===============================// Admin Menu Exit //===========================

void MainWindow::on_db_exit_admin_Button_clicked()
{
    ui->AdminGroupBox->hide();
    ui->WorkGroupBox->show();
    ui->molar_solutions_menubur->setEnabled(true);
    ui->normal_concentration_menubur->setEnabled(true);
    ui->ligation_menubur->setEnabled(true);

    ui->AdminGroupBox->move(0,380);
    ui->WorkGroupBox->move(0, 0);
    on_molar_solutions_menubur_triggered();
}

//===============================// Menubur Menu //==============================

void MainWindow::on_molar_solutions_menubur_triggered()
{
    ui->molar_solutions_groupBox->show();
    ui->ligation_groupBox->hide();
    ui->normal_concentration_groupBox->hide();

    ui->formula_input_for_parsing_LineEdit->show();
    ui->molecular_weight_output_LineEdit->show();
    ui->formula_for_parsing_input_label->show();
    ui->molecular_weight_output_label->show();

    ui->molar_solutions_groupBox->move(10,80);
    ui->ligation_groupBox->move(760,0);
    ui->normal_concentration_groupBox->move(760,180);
}

void MainWindow::on_normal_concentration_menubur_triggered()
{
    ui->normal_concentration_groupBox->show();
    ui->molar_solutions_groupBox->hide();
    ui->ligation_groupBox->hide();

    ui->formula_input_for_parsing_LineEdit->show();
    ui->molecular_weight_output_LineEdit->show();
    ui->formula_for_parsing_input_label->show();
    ui->molecular_weight_output_label->show();

    ui->molar_solutions_groupBox->move(760,180);
    ui->ligation_groupBox->move(760,0);
    ui->normal_concentration_groupBox->move(10,80);
}

void MainWindow::on_ligation_menubur_triggered()
{
    ui->ligation_groupBox->show();
    ui->molar_solutions_groupBox->hide();
    ui->normal_concentration_groupBox->hide();

    ui->formula_input_for_parsing_LineEdit->hide();
    ui->molecular_weight_output_LineEdit->hide();
    ui->formula_for_parsing_input_label->hide();
    ui->molecular_weight_output_label->hide();

    ui->molar_solutions_groupBox->move(760,180);
    ui->ligation_groupBox->move(10,40);
    ui->normal_concentration_groupBox->move(760,0);
}

//===============================// Normal Concentration Check Boxes //===============

void MainWindow::on_normal_concentration_concentration_radioButton_clicked()
{

    if(ui->normal_concentration_concentration_radioButton->isChecked()){

        ui->normal_concentration_volume_LineEdit->setReadOnly(false);
        ui->normal_concentration_mass_LineEdit->setReadOnly(false);
        ui->normal_concentration_concentration_LineEdit->setReadOnly(true);

        if(ui->normal_concentration_mass_radioButton->isChecked()){

            ui->normal_concentration_mass_radioButton->click();
        }

        if(ui->normal_concentration_volume_radioButton->isChecked()){

            ui->normal_concentration_volume_radioButton->click();
        }
    }

}

void MainWindow::on_normal_concentration_volume_radioButton_clicked()
{

    if(ui->normal_concentration_volume_radioButton->isChecked()){

        ui->normal_concentration_mass_LineEdit->setReadOnly(false);
        ui->normal_concentration_concentration_LineEdit->setReadOnly(false);
        ui->normal_concentration_volume_LineEdit->setReadOnly(true);

        if(ui->normal_concentration_mass_radioButton->isChecked()){

            ui->normal_concentration_mass_radioButton->click();
        }

        if(ui->normal_concentration_concentration_radioButton->isChecked()){

            ui->normal_concentration_concentration_radioButton->click();
        }
    }

}

void MainWindow::on_normal_concentration_mass_radioButton_clicked()
{

    if(ui->normal_concentration_mass_radioButton->isChecked()){

        ui->normal_concentration_volume_LineEdit->setReadOnly(false);
        ui->normal_concentration_concentration_LineEdit->setReadOnly(false);
        ui->normal_concentration_mass_LineEdit->setReadOnly(true);

        if(ui->normal_concentration_volume_radioButton->isChecked()){

            ui->normal_concentration_volume_radioButton->click();
        }

        if(ui->normal_concentration_concentration_radioButton->isChecked()){

            ui->normal_concentration_concentration_radioButton->click();
        }
    }

}

//===============================// Molar Solutions Check Boxes //===============

void MainWindow::on_molar_solutions_volume_radioButton_clicked()
{

    if(ui->molar_solutions_volume_radioButton->isChecked()){

        ui->molar_solutions_molar_mass_input_LineEdit->setReadOnly(false);
        ui->molar_solutions_molar_concentration_input_LineEdit->setReadOnly(false);
        ui->molar_solutions_volume_input_LineEdit->setReadOnly(true);

        if(ui->molar_solutions_mass_radioButton->isChecked()){

            ui->molar_solutions_mass_radioButton->click();
        }

        if(ui->molar_solutions_molar_concentration_radioButton->isChecked()){

            ui->molar_solutions_molar_concentration_radioButton->click();
        }
    }

}


void MainWindow::on_molar_solutions_molar_concentration_radioButton_clicked()
{

    if(ui->molar_solutions_molar_concentration_radioButton->isChecked()){

        ui->molar_solutions_molar_mass_input_LineEdit->setReadOnly(false);
        ui->molar_solutions_volume_input_LineEdit->setReadOnly(false);
        ui->molar_solutions_molar_concentration_input_LineEdit->setReadOnly(true);

        if(ui->molar_solutions_mass_radioButton->isChecked()){

            ui->molar_solutions_mass_radioButton->click();
        }

        if(ui->molar_solutions_volume_radioButton->isChecked()){

            ui->molar_solutions_volume_radioButton->click();
        }
    }

}

void MainWindow::on_molar_solutions_mass_radioButton_clicked()
{

    if(ui->molar_solutions_mass_radioButton->isChecked()){

        ui->molar_solutions_molar_concentration_input_LineEdit->setReadOnly(false);
        ui->molar_solutions_volume_input_LineEdit->setReadOnly(false);
        ui->molar_solutions_molar_mass_input_LineEdit->setReadOnly(true);

        if(ui->molar_solutions_molar_concentration_radioButton->isChecked()){

            ui->molar_solutions_molar_concentration_radioButton->click();
        }

        if(ui->molar_solutions_volume_radioButton->isChecked()){

            ui->molar_solutions_volume_radioButton->click();
        }
    }

}

//===============================// Admin Group Box //===========================

bool MainWindow::add_new_db_data (const QString& acid_limit_input, const QString& equivalent_limit) {


    if(not DBWorker::Instence().AddNewEquivalent(acid_limit_input, equivalent_limit.toInt())) {

        ui->statusbar->showMessage("Ошибка! Новое поле не добавлено", 4000);

        return false;

    }

    if(not DBWorker::Instence().ReloadTableBuffer()){

        ui->statusbar->showMessage("Ошибка! Буфер не обновлен", 4000);

        return false;

    }

    return true;
}

bool MainWindow::delete_db_data (const QString& acid_limit_input) {

    if(not DBWorker::Instence().DeleteEquivalent(acid_limit_input)){

        ui->statusbar->showMessage("Ошибка! Поле не удалено", 4000);

        return false;

    }

    if(not DBWorker::Instence().ReloadTableBuffer()){

        ui->statusbar->showMessage("Ошибка! Буфер не обновлен", 4000);

        return false;

    }

    return true;
}

void MainWindow::reload_db_output(){

    if(DBWorker::Instence().GetAllInfoFromDB()){

        ui->db_table_output_View->setModel(DBWorker::Instence().GetModal());

    } else {

        ui->statusbar->showMessage("Ошибка! Данные из базы не загруженны", 4000);

    }
}

void MainWindow::on_db_add_data_input_Button_clicked()
{

    QString error = CheckDBInput
            (ui->db_acid_limit_input_LineEdit->text(),
             ui->db_equivalent_input_LineEdit->text());

    if (error.isEmpty()) {

        if (add_new_db_data(ui->db_acid_limit_input_LineEdit->text(), ui->db_equivalent_input_LineEdit->text())) {

            reload_db_output();

        }

    }else {

        ui->statusbar->showMessage(error, 4000);

    }

}

void MainWindow::on_db_delete_data_Button_clicked()
{

    QString error = CheckDBInput
            (ui->db_acid_limit_input_LineEdit->text(), "1");

    if(error.isEmpty()) {

        if(delete_db_data(ui->db_acid_limit_input_LineEdit->text())){

            reload_db_output();

        }

    }else {

        ui->statusbar->showMessage(error, 4000);

    }

}

//===============================// Calculate Molar Solutions Methods //==========================

void MainWindow::calculate_molar_solutions_volume(){

    QString error = CheckInput(
                ui->formula_input_for_parsing_LineEdit->text(),
                ui->molar_solutions_molar_concentration_input_LineEdit->text(),
                ui->molar_solutions_molar_mass_input_LineEdit->text()
                );

    if(error.isEmpty()) {

        const float molecular_weigth =
                ConvertToMolecularWeight(
                    ui->formula_input_for_parsing_LineEdit->text().replace(",","."),
                    error);

        if(error.isEmpty()){

            const float molar_concentration = ui->molar_solutions_molar_concentration_input_LineEdit->text().replace(",",".").toFloat();
            const float molar_mass = ui->molar_solutions_molar_mass_input_LineEdit->text().replace(",",".").toFloat();

            ui->molecular_weight_output_LineEdit->setText(QString::number(molecular_weigth));

            ui->molar_solutions_volume_input_LineEdit->setText(
                        QString::number(Volume(molecular_weigth,
                                               molar_concentration,
                                               molar_mass
                                               )));

        }else{

            ui->statusbar->showMessage(error, 4000);

        }


    }else {

        ui->statusbar->showMessage(error, 4000);

    }
}

void MainWindow::calculate_molar_solutions_molar_concentration(){

    QString error = CheckInput(
                ui->formula_input_for_parsing_LineEdit->text(),
                ui->molar_solutions_volume_input_LineEdit->text(),
                ui->molar_solutions_molar_mass_input_LineEdit->text()
                );

    if(error.isEmpty()){

        const float molecular_weigth =
                ConvertToMolecularWeight(
                    ui->formula_input_for_parsing_LineEdit->text().replace(",","."),
                    error);

        if(error.isEmpty()){

            const float volume = ui->molar_solutions_volume_input_LineEdit->text().replace(",",".").toFloat();
            const float molar_mass = ui->molar_solutions_molar_mass_input_LineEdit->text().replace(",",".").toFloat();

            ui->molecular_weight_output_LineEdit->setText(QString::number(molecular_weigth));

            ui->molar_solutions_molar_concentration_input_LineEdit->setText(
                        QString::number(MolarConcentration(molecular_weigth,
                                                           volume,
                                                           molar_mass
                                                           )));
        }else{

            ui->statusbar->showMessage(error, 4000);

        }

    }else{

        ui->statusbar->showMessage(error, 4000);

    }
}

void MainWindow::calculate_molar_solutions_mass(){

    QString error = CheckInput(
                ui->formula_input_for_parsing_LineEdit->text(),
                ui->molar_solutions_volume_input_LineEdit->text(),
                ui->molar_solutions_molar_concentration_input_LineEdit->text()
                );

    if(error.isEmpty()){

        const float molecular_weigth =
                ConvertToMolecularWeight(
                    ui->formula_input_for_parsing_LineEdit->text().replace(",","."),
                    error);

        if(error.isEmpty()){

            const float volume = ui->molar_solutions_volume_input_LineEdit->text().replace(",",".").toFloat();
            const float molar_concentration = ui->molar_solutions_molar_concentration_input_LineEdit->text().replace(",",".").toFloat();

            ui->molecular_weight_output_LineEdit->setText(QString::number(molecular_weigth));

            ui->molar_solutions_molar_mass_input_LineEdit->setText(
                        QString::number(Mass(molecular_weigth,
                                             volume,
                                             molar_concentration
                                             )));
        }else{

            ui->statusbar->showMessage(error, 4000);
        }

    }else {

        ui->statusbar->showMessage(error, 4000);

    }

}

//===============================// Calculate Normal Concentration Methods //==========================

void MainWindow::calculate_normal_concentration_volume(){

    QString error = CheckInput(
                ui->formula_input_for_parsing_LineEdit->text(),
                ui->normal_concentration_concentration_LineEdit->text(),
                ui->normal_concentration_mass_LineEdit->text()
                );

    if(error.isEmpty()){

        const float molecular_weigth =
                ConvertToMolecularWeight(
                    ui->formula_input_for_parsing_LineEdit->text().replace(",","."),
                    error);

        if(error.isEmpty()){

            const float concentration = ui->normal_concentration_concentration_LineEdit->text().replace(",",".").toFloat();
            const float mass = ui->normal_concentration_mass_LineEdit->text().replace(",",".").toFloat();
            const size_t equivalent = FindEquivalent(ui->formula_input_for_parsing_LineEdit->text());

            ui->molecular_weight_output_LineEdit->setText(QString::number(molecular_weigth));

            ui->normal_concentration_volume_LineEdit->setText(
                        QString::number(Volume(molecular_weigth / equivalent, // molecular weigth of equivalent
                                             concentration,
                                             mass)));

        }else{

            ui->statusbar->showMessage(error, 4000);

        }

    }else {

        ui->statusbar->showMessage(error, 4000);

    }

}

void MainWindow::calculate_normal_concentration_concentration(){

    QString error = CheckInput(
                ui->formula_input_for_parsing_LineEdit->text(),
                ui->normal_concentration_mass_LineEdit->text(),
                ui->normal_concentration_volume_LineEdit->text()
                );

    if(error.isEmpty()){

        const float molecular_weigth =
                ConvertToMolecularWeight(
                    ui->formula_input_for_parsing_LineEdit->text().replace(",","."),
                    error);

        if(error.isEmpty()){

            const float mass = ui->normal_concentration_mass_LineEdit->text().replace(",",".").toFloat();
            const float volume = ui->normal_concentration_volume_LineEdit->text().replace(",",".").toFloat();
            const size_t equivalent = FindEquivalent(ui->formula_input_for_parsing_LineEdit->text());

            ui->molecular_weight_output_LineEdit->setText(QString::number(molecular_weigth));

            ui->normal_concentration_concentration_LineEdit->setText(
                        QString::number(MolarConcentration(molecular_weigth / equivalent, // molecular weigth of equivalent
                                            volume,
                                            mass)));

        }else{

            ui->statusbar->showMessage(error, 4000);

        }

    }else {

        ui->statusbar->showMessage(error, 4000);

    }

}

void MainWindow::calculate_normal_concentration_mass(){

    QString error = CheckInput(
                ui->formula_input_for_parsing_LineEdit->text(),
                ui->normal_concentration_concentration_LineEdit->text(),
                ui->normal_concentration_volume_LineEdit->text()
                );

    if(error.isEmpty()){

        const float molecular_weigth =
                ConvertToMolecularWeight(
                    ui->formula_input_for_parsing_LineEdit->text().replace(",","."),
                    error);

        if(error.isEmpty()){

            const float concentration = ui->normal_concentration_concentration_LineEdit->text().replace(",",".").toFloat();
            const float volume = ui->normal_concentration_volume_LineEdit->text().replace(",",".").toFloat();
            const size_t equivalent = FindEquivalent(ui->formula_input_for_parsing_LineEdit->text());

            ui->molecular_weight_output_LineEdit->setText(QString::number(molecular_weigth));

            ui->normal_concentration_mass_LineEdit->setText(
                        QString::number(Mass(molecular_weigth / equivalent, // molecular weigth of equivalent
                                             volume,
                                             concentration)));

        }else{

            ui->statusbar->showMessage(error, 4000);

        }

    }else {

        ui->statusbar->showMessage(error, 4000);

    }

}

void MainWindow::calculate_ligation(){

   QString error = CheckLigationInput(ui->ligation_mass_input_LineEdit->text(),
                        ui->ligation_vector_length_input_LineEdit->text(),
                        ui->ligation_vector_to_insert_ratio_Input_left_LineEdit->text(),
                        ui->ligation_vector_to_insert_ratio_Input_right_LineEdit->text(),
                        ui->ligation_length_insertion_Input_LineEdit->text());

    if(error.isEmpty()) {

        const float mass = ui->ligation_mass_input_LineEdit->text().replace(",",".").toFloat();
        const float vector_length = ui->ligation_vector_length_input_LineEdit->text().replace(",",".").toFloat();
        const float left_ratio_insertion = ui->ligation_vector_to_insert_ratio_Input_left_LineEdit->text().replace(",",".").toFloat();
        const float right_ratio_insertion = ui->ligation_vector_to_insert_ratio_Input_right_LineEdit->text().replace(",",".").toFloat();
        const float length_insertion = ui->ligation_length_insertion_Input_LineEdit->text().replace(",",".").toFloat();

        ui->ligation_insertion_mass_Output_LineEdit->setText(
                    QString::number(MassInsertion(mass, vector_length, left_ratio_insertion, right_ratio_insertion, length_insertion))
                    );

    }else {

        ui->statusbar->showMessage(error, 4000);

    }

}

void MainWindow::on_calculate_Button_clicked()
{

    if(ui->molar_solutions_groupBox->isVisible()) {

        if(ui->molar_solutions_volume_radioButton->isChecked()){

            calculate_molar_solutions_volume();

        } else if(ui->molar_solutions_molar_concentration_radioButton->isChecked()) {

            calculate_molar_solutions_molar_concentration();

        } else if(ui->molar_solutions_mass_radioButton->isChecked()){

            calculate_molar_solutions_mass();

        }

    } else if (ui->normal_concentration_groupBox->isVisible()){

        if(ui->normal_concentration_volume_radioButton->isChecked()){

            calculate_normal_concentration_volume();

        } else if(ui->normal_concentration_concentration_radioButton->isChecked()) {

            calculate_normal_concentration_concentration();

        } else if(ui->normal_concentration_mass_radioButton->isChecked()){

            calculate_normal_concentration_mass();

        }

    } else if (ui->ligation_groupBox->isVisible()){

        calculate_ligation();

    }
}

//===============================// Clear Method //================================

void MainWindow::on_clear_Button_clicked()
{
    if(ui->molar_solutions_groupBox->isVisible()) {

        ui->molar_solutions_volume_input_LineEdit->clear();
        ui->molar_solutions_molar_concentration_input_LineEdit->clear();
        ui->molar_solutions_molar_mass_input_LineEdit->clear();
        ui->formula_input_for_parsing_LineEdit->clear();
        ui->molecular_weight_output_LineEdit->clear();

    } else if (ui->normal_concentration_groupBox->isVisible()){

        ui->normal_concentration_concentration_LineEdit->clear();
        ui->normal_concentration_volume_LineEdit->clear();
        ui->normal_concentration_mass_LineEdit->clear();
        ui->formula_input_for_parsing_LineEdit->clear();
        ui->molecular_weight_output_LineEdit->clear();

    } else if (ui->ligation_groupBox->isVisible()){

        ui->ligation_mass_input_LineEdit->clear();
        ui->ligation_vector_length_input_LineEdit->clear();
        ui->ligation_length_insertion_Input_LineEdit->clear();
        ui->ligation_vector_to_insert_ratio_Input_left_LineEdit->clear();
        ui->ligation_vector_to_insert_ratio_Input_right_LineEdit->clear();
        ui->ligation_insertion_mass_Output_LineEdit->clear();

    }

}
