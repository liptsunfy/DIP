#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>
#include <QtWidgets/QSlider>

using namespace QtDataVisualization;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

private:
    QWidget *graphContainer;  // 图表的容器
    Q3DSurface *graph3D;      // 图表
    QSurface3DSeries *series;

    QHeightMapSurfaceDataProxy *m_heightMapProxy;
    QSurfaceDataProxy *m_sqrtSinProxy;
    QSurface3DSeries *m_heightMapSeries;
    QSurface3DSeries *m_sqrtSinSeries;

    QSlider *m_axisMinSliderX;
    QSlider *m_axisMaxSliderX;
    QSlider *m_axisMinSliderZ;
    QSlider *m_axisMaxSliderZ;

    float m_rangeMinX;
    float m_rangeMinZ;
    float m_stepX;
    float m_stepZ;
    int m_heightMapWidth;
    int m_heightMapHeight;

    void setAxisXRange(float min, float max);
    void setAxisZRange(float min, float max);
    void fillSqrtSinProxy();
    void iniGraph3D();

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_comboCamera_currentIndexChanged(int index);

    void on_sliderH_valueChanged(int value); //水平旋转

    void on_sliderV_valueChanged(int value);  // 垂直旋转

    void on_sliderZoom_valueChanged(int value);

    void on_cBoxTheme_currentIndexChanged(int index);

    void on_spinBox_valueChanged(int arg1);

    void on_checkBox_4_clicked(bool checked);

private:
    Ui::Dialog *ui;

};


#endif // DIALOG_H
