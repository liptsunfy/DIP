#include "dialog.h"
#include "ui_dialog.h"
#include "MyFun.h"

#include "mainwindow.cpp"

#include <QHBoxLayout>


Dialog::Dialog(QWidget *parent) :
QDialog(parent),
ui(new Ui::Dialog)
{
    ui->setupUi(this);
    iniGraph3D();
}



Dialog::~Dialog()
{
    delete ui;
}



void Dialog::iniGraph3D()
{
    // 创建图表
    graph3D =new Q3DSurface;

    QWidget *graphContainer=QWidget::createWindowContainer(graph3D);
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(graphContainer);
    ui->widget->setLayout(layout);

    
    // 将坐标轴添加到图像
    QValue3DAxis *axisX = new QValue3DAxis;
    axisX->setRange(0, m_imgHeightOut);
    QValue3DAxis *axisY = new QValue3DAxis;
    axisY->setRange(0, m_imgWidthOut);
    QValue3DAxis *axisZ = new QValue3DAxis;


    graph3D->setAxisX(axisX);
    graph3D->setAxisY(axisY);
    graph3D->setAxisZ(axisZ);


    // 载入数据  对重构结果进行解包裹
    m_dPhaseDif = 2 * PI;
    PhaseUnwrap3(m_rImgDataOut, m_imgWidthOut, m_nBitCountOut, m_imgHeightOut,m_dPhaseDif);

    // 构建二维数组
    float *array_temp[m_imgHeightOut];
    for(int i=0;i<m_imgHeightOut;i++){
        array_temp[i]=(float *)malloc(sizeof(float) * m_imgWidthOut);  // 为每个指针申请开设N字符的存储空间
    }

    int lineByte = (m_imgWidthOut * m_nBitCountOut / 8 + 3) / 4 * 4;

    for (int i = 0; i < m_imgHeightOut; i++){
        for (int j = 0; j < m_imgWidthOut; j++){
           array_temp[i][j] = double(m_sImgDataOut[i*lineByte+j] * (255 / m_dPhaseDif));
        }
    }


    // 创建数据对象
    QSurfaceDataArray *dataSet = new QSurfaceDataArray;

    dataSet->reserve(m_imgHeightOut * m_imgWidthOut * 2);
    for (int i=0; i<m_imgHeightOut; i++){
        QSurfaceDataRow *dataRow = new QSurfaceDataRow(m_imgWidthOut * 2);

        int index = 0;
        for (int j = 0; j<m_imgWidthOut; j++){
            float x = i;
            float y = j;
            float z = array_temp[i][j];

            (*dataRow)[index++].setPosition(QVector3D(x, y, z));
        }

        *dataSet << dataRow;
    }


    // 创建序列，加入数据，添加到坐标系中
    series = new QSurface3DSeries;
    graph3D->addSeries(series);
    series->dataProxy()->resetArray(dataSet);
    graph3D->show();

    // 设置颜色区域

    delete *array_temp;
}


// 变换视角
void Dialog::on_comboCamera_currentIndexChanged(int index)
{
    Q3DCamera::CameraPreset cameraPos=Q3DCamera::CameraPreset(index);  // 将序号转换成Q3DCamera::CameraPreset类型
    graph3D->scene()->activeCamera()   // 获取当前图标视角
        ->setCameraPreset(cameraPos);  // 设置视角
}


// 水平旋转
void Dialog::on_sliderH_valueChanged(int value)
{
    Q_UNUSED(value);
    int xRot=ui->sliderH->value();
    graph3D->scene()->activeCamera()->setXRotation(xRot);
}


// 垂直旋转
void Dialog::on_sliderV_valueChanged(int value)
{
    Q_UNUSED(value);
    int yRot=ui->sliderV->value();
    graph3D->scene()->activeCamera()->setYRotation(yRot);
}


// 缩放
void Dialog::on_sliderZoom_valueChanged(int value)
{
    Q_UNUSED(value);
    int zoom=ui->sliderZoom->value();
    graph3D->scene()->activeCamera()->setZoomLevel(zoom);
}


// 主题
void Dialog::on_cBoxTheme_currentIndexChanged(int index)
{
    Q3DTheme *currentTheme=graph3D->activeTheme();
    currentTheme->setType(Q3DTheme::Theme(index));
}



void Dialog::on_spinBox_valueChanged(int arg1)
{
    QFont font=graph3D->activeTheme()->font();
    font.setPointSize(arg1);
    graph3D->activeTheme()->setFont(font);
}



void Dialog::on_checkBox_4_clicked(bool checked)
{
    graph3D->axisZ()->setReversed(checked);
}
