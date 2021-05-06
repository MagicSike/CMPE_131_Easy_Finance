#include "form.h"
#include "ui_form.h"

using namespace std;
QT_CHARTS_USE_NAMESPACE

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::Form(std::vector<std::vector<QString>> *a, QVector<QString> *names, int t_graphID, QWidget *parent)
    :QWidget(parent), ui(new Ui::Form)
{

    switch(t_graphID)
    {
    case pie:
        pieSeries(a, names);
        break;
    case bar:
        barSeries(a, names);
        break;
    case hBar:
        hBarSeries(a, names);
        break;
    case box:
        boxSeries(a, names);
        break;
    case lineBar:
        lineBarSeires(a, names);
        break;
    }
}

Form::Form(std::vector<std::vector<QString> > x, std::vector<std::vector<QString> > y, QVector<QString> *names, int t_graphID, QWidget *parent)
    : QWidget(parent), ui(new Ui::Form)
{
    switch(t_graphID)
    {
    case line:
        lineSeries(x, y, names);
        break;
    case scatter:
        scatterSeries(x, y, names);
        break;
    case area:
        areaSeries(x, y, names);
        break;
    }
}

void Form::lineSeries(std::vector<std::vector<QString>> x, std::vector<std::vector<QString>> y, QVector<QString> *names)
{
    QLineSeries *isrt;

    QChart *chart = new QChart();
    chart->legend()->setAlignment(Qt::AlignBottom);
    int columnName = 0;
    for(unsigned int column = 0; column < x.size(); column++)
    {
        isrt = new QLineSeries();
        isrt->setName(names->at(columnName));
        columnName = columnName + 2;
        for(unsigned int row = 0; row < x.at(column).size(); row++)
        {
            double value = x.at(column).at(row).toDouble();
            isrt->append(value, y.at(column).at(row).toDouble());
        }
        chart->addSeries(isrt);
    }

    chart->createDefaultAxes();

    chart->setTitle("Line Series");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("Line Series");
    window->setCentralWidget(chartView);
    window->resize(400, 300);
    window->show();
}

void Form::barSeries(std::vector<std::vector<QString>> *a, QVector<QString> *names)
{
    QBarSet *set;
    QBarSeries *series = new QBarSeries();

    for (unsigned int column = 1; column < a->size(); column++)
    {
        set = new QBarSet(names->at(column));
        for(unsigned int row = 0; row < a->at(column).size(); row++)
        {
            if(a->at(0).size() - 1 < row)
                break;

            set->append(a->at(column).at(row).toDouble());
        }

        series->append(set);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    for (unsigned int category = 0; category < a->at(0).size(); category++)
    {
        axisX->append(a->at(0).at(category));
    }

    QChart *chart = new QChart();
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->addSeries(series);
    chart->setTitle("Bar Series");

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chart->setAnimationOptions(QChart::SeriesAnimations);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("Bar Series");
    window->setCentralWidget(chartView);
    window->resize(400, 300);
    window->show();
}

void Form::scatterSeries(std::vector<std::vector<QString>> x, std::vector<std::vector<QString>> y, QVector<QString> *names)
{
    QScatterSeries *isrt;

    QChart *chart = new QChart();
    chart->legend()->setAlignment(Qt::AlignBottom);
    int columnName = 0;
    for(unsigned int column = 0; column < x.size(); column++)
    {
        isrt = new QScatterSeries();
        isrt->setName(names->at(columnName));
        columnName = columnName + 2;
        for(unsigned int row = 0; row < x.at(column).size(); row++)
        {
            double value = x.at(column).at(row).toDouble();
            isrt->append(value, y.at(column).at(row).toDouble());
        }
        chart->addSeries(isrt);
    }

    chart->createDefaultAxes();

    chart->setTitle("Scatter Series");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("Scatter Series");
    window->setCentralWidget(chartView);
    window->resize(400, 300);
    window->show();

}

void Form::pieSeries(std::vector<std::vector<QString>> *a, QVector<QString> *names)
{
    double total = 0;
    unsigned int size = names->size();
    double *individual = new double[size];

    QPieSeries *series = new QPieSeries();
    for(unsigned column = 0; column < a->size(); column++)
    {
        individual[column] = 0;
        for(unsigned int row = 0; row < a->at(column).size(); row++)
        {
            total += a->at(column).at(row).toDouble();
            individual[column] += a->at(column).at(row).toDouble();
        }
    }

    for(int category = 0; category < names->size(); category++)
    {

        series->append(names->at(category), (individual[category]/total));

    }
    delete[] individual;
    individual = nullptr;

    series->setLabelsVisible();
    series->setLabelsPosition(QPieSlice::LabelInsideHorizontal);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Pie Chart");
    chart->legend()->setAlignment(Qt::AlignRight);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("Pie Series");
    window->setCentralWidget(chartView);
    window->resize(400, 300);
    window->show();

}

void Form::boxSeries(std::vector<std::vector<QString> > *a, QVector<QString> *names)
{
    QBoxPlotSeries *plot = new QBoxPlotSeries();

    QList<qreal> *sortedList;
    QBoxSet *set;
    for(unsigned int column = 0; column < a->size(); column++)
    {
        sortedList = new QList<qreal>;
        for (unsigned int row = 0; row < a->at(column).size(); row++)
        {
            sortedList->append(a->at(column).at(row).toDouble());
        }

        if(sortedList->size() > 1)
        {
            int count = sortedList->count();
            std::sort(sortedList->begin(), sortedList->end());
            set = new QBoxSet(names->at(column));
            set->setValue(QBoxSet::LowerExtreme, sortedList->first());
            set->setValue(QBoxSet::UpperExtreme, sortedList->last());
            set->setValue(QBoxSet::Median, findMedian(0, count, sortedList));
            set->setValue(QBoxSet::LowerQuartile, findMedian(0, count / 2, sortedList));
            set->setValue(QBoxSet::UpperQuartile, findMedian(count / 2 + (count % 2), count, sortedList));

            plot->append(set);

        }
    }

    QChart *chart = new QChart();
    chart->addSeries(plot);
    chart->setTitle("Box and Whisker Series");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();
    chart->legend()->setVisible(false);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Box and Whisker Series");
    window->setCentralWidget(chartView);
    window->resize(800, 600);
    window->show();
}

void Form::areaSeries(std::vector<std::vector<QString>> x, std::vector<std::vector<QString>> y, QVector<QString> *names)
{
    QLineSeries *seriesOrigin;
    QLineSeries *series;
    QAreaSeries *areaSeries;

    QChart *chart = new QChart();
    chart->legend()->setAlignment(Qt::AlignRight);

    QPen pen(0x059605);
    pen.setWidth(3);
    QLinearGradient gradient(QPointF(0, 0), QPointF(0, 1));
    gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
    int columnName = 0;
    for(unsigned int column = 0; column < x.size(); column++)
    {
        series = new QLineSeries();
        seriesOrigin =  new QLineSeries();

        for(unsigned int row = 0; row < x.at(column).size(); row++)
        {
            double value = x.at(column).at(row).toDouble();
            series->append(value, y.at(column).at(row).toDouble());
            seriesOrigin->append(value, 0);
        }

        areaSeries = new QAreaSeries(series, seriesOrigin);
        areaSeries->setPen(pen);
        areaSeries->setOpacity(0.5);
        areaSeries->setName(names->at(columnName));
        columnName = columnName + 2;
        chart->addSeries(areaSeries);
    }

    chart->setTitle("Area Chart Series");
    chart->createDefaultAxes();
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->setBackgroundVisible(true);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow *window = new QMainWindow();
    window->setWindowTitle("Area Series");
    window->setCentralWidget(chartView);
    window->resize(800, 600);
    window->show();

}

void Form::lineBarSeires(std::vector<std::vector<QString> > *a, QVector<QString> *names)
{
    QBarSet *set;
    QBarSeries *series = new QBarSeries();

    QLineSeries *isrt = new QLineSeries();
    isrt->setName(names->at(1));

    for(unsigned int row = 0; row < a->at(1).size(); row++) // line series begin
    {
        double value = a->at(1).at(row).toDouble();
        isrt->append(row, value);
    }

    for (unsigned int column = 2; column < a->size(); column++) // bar graphs begin
    {
        set = new QBarSet(names->at(column));
        for(unsigned int row = 0; row < a->at(column).size(); row++)
        {
            if(a->at(0).size() - 1 < row)
                break;

            set->append(a->at(column).at(row).toDouble());
        }

        series->append(set);
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    for (unsigned int category = 0; category < a->at(0).size(); category++)
    {
        axisX->append(a->at(0).at(category));
    }

    QChart *chart = new QChart();
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->addSeries(series);
    chart->addSeries(isrt);
    chart->setTitle("Line Bar Series");

    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    isrt->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    isrt->attachAxis(axisY);

    chart->setAnimationOptions(QChart::SeriesAnimations);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("LineBar Series");
    window->setCentralWidget(chartView);
    window->resize(400, 300);
    window->show();
}

void Form::hBarSeries(std::vector<std::vector<QString> > *a, QVector<QString> *names)
{
    QBarSet *set;
     QHorizontalBarSeries *series = new  QHorizontalBarSeries();

    for (unsigned int column = 1; column < a->size(); column++)
    {
        set = new QBarSet(names->at(column));
        for(unsigned int row = 0; row < a->at(column).size(); row++)
        {
            if(a->at(0).size() - 1 < row)
                break;

            set->append(a->at(column).at(row).toDouble());
        }

        series->append(set);
    }

    QBarCategoryAxis *axisY = new QBarCategoryAxis();
    for (unsigned int category = 0; category < a->at(0).size(); category++)
    {
        axisY->append(a->at(0).at(category));
    }

    QChart *chart = new QChart();
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->addSeries(series);
    chart->setTitle("Bar Series");

    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QValueAxis *axisX = new QValueAxis();
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    chart->setAnimationOptions(QChart::SeriesAnimations);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QMainWindow *window = new QMainWindow;
    window->setWindowTitle("Horizontal Bar Series");
    window->setCentralWidget(chartView);
    window->resize(400, 300);
    window->show();
}


qreal Form::findMedian(int begin, int end, QList<qreal> *sortedList)
{
    int count = end - begin;
    if (count % 2)
        return sortedList->at(count / 2 + begin);
    else
    {
        qreal right = sortedList->at(count / 2 + begin);
        qreal left = sortedList->at(count / 2 - 1 + begin);
        return (right + left) / 2.0;
    }
}

Form::~Form()
{
    delete ui;
}
