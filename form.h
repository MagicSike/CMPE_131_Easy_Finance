#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QtDebug>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QBoxPlotSeries>
#include <QBarSet>
#include <QBarSeries>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QScatterSeries>
#include <QAreaSeries>
#include <QHorizontalBarSeries>
#include <QStackedBarSeries>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    Form(std::vector<std::vector<QString>> *a, QVector<QString> *names, int graphID, QWidget *parent = nullptr);
    Form(std::vector<std::vector<QString>> x, std::vector<std::vector<QString>> y, QVector<QString> *names, int graphID, QWidget *parent = nullptr);
    void lineSeries(std::vector<std::vector<QString>> a, std::vector<std::vector<QString>> y, QVector<QString> *names);
    void barSeries(std::vector<std::vector<QString>> *a, QVector<QString> *names);
    void scatterSeries(std::vector<std::vector<QString>> a, std::vector<std::vector<QString>> y, QVector<QString> *names);
    void pieSeries(std::vector<std::vector<QString>> *a, QVector<QString> *names);
    void boxSeries(std::vector<std::vector<QString>> *a, QVector<QString> *names);
    void areaSeries(std::vector<std::vector<QString>> a, std::vector<std::vector<QString>> y, QVector<QString> *names);
    void lineBarSeires(std::vector<std::vector<QString>> *a, QVector<QString> *names); // assumes the first categroy is x-axis values, second to be line series, the rest is bar graphs
    void hBarSeries(std::vector<std::vector<QString>> *a, QVector<QString> *names);
    ~Form();

private:

    qreal findMedian(int begin, int end, QList<qreal> *sortedList);

    enum ID {line, scatter, bar, pie, box, area, lineBar, hBar};
    Ui::Form *ui;
};

#endif // FORM_H
