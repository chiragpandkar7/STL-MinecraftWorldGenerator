#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Voxelize.h"

class Voxelize : public QMainWindow
{
    Q_OBJECT

public:
    Voxelize(QWidget *parent = nullptr);
    ~Voxelize();

private:
    Ui::VoxelizeClass ui;
};
