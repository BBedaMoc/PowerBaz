#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog1.h"
#include "dialog2.h"
#include "dialog3.h"
#include <QString>
#include <QTextCodec>
#include "qfilm.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QTextStream>
#include "filmlistitem.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadList();
    setLicznik(elem.length());
}

MainWindow::~MainWindow()
{
    writeList();
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    ui->listWidget->setGeometry(5,75,this->width()-10,this->height()-125);
    ui->comboBox->setGeometry(this->width()-130,ui->comboBox->pos().y(),ui->comboBox->size().width(),ui->comboBox->size().height());
    ui->radioButton1->setGeometry(this->width()-100,ui->radioButton1->pos().y(),ui->radioButton1->size().width(),ui->radioButton1->size().height());
    ui->radioButton2->setGeometry(this->width()-50,ui->radioButton2->pos().y(),ui->radioButton2->size().width(),ui->radioButton2->size().height());
    ui->label->setGeometry(this->width()-130,ui->label->pos().y(),ui->label->size().width(),ui->label->size().height());
    ui->pushButton->setGeometry(this->width()-220,ui->pushButton->pos().y(),ui->pushButton->size().width(),ui->pushButton->size().height());
    ui->lineEdit->setGeometry(ui->lineEdit->pos().x(),ui->lineEdit->pos().y(),this->width()-150,ui->lineEdit->size().height());

}

void MainWindow::writeList(){
    QFile file(QString("data.pbdb"));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return ;
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE pbdb>");
    writer.writeStartElement("document");
    writer.writeStartElement("films");
    for(int i=0;i<elem.length();++i){
        writeFilm(elem.at(i), &writer);
    }
    writer.writeEndElement();
    writer.writeEndElement();
    writer.writeEndDocument();
    file.close();
}

void MainWindow::loadList(){
    QFile file(QString("data.pbdb"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return ;

    elem.clear();
    QXmlStreamReader reader;
    reader.setDevice(&file);
    qFilm *nowRead=NULL;

    while(!reader.atEnd()){
        QXmlStreamReader::TokenType type =reader.readNext();
        if(type==QXmlStreamReader::TokenType::StartElement){
            QString name=reader.name().toString();
            QXmlStreamAttributes attributes=reader.attributes();
               if(name==QString("film")){
                   qFilm *newFilm = new qFilm();
                   elem.append(newFilm);
                   nowRead=newFilm;
               }
               else if(name==QString("titles")){
                   if(nowRead!=NULL)
                       if(attributes.length()==2){
                           nowRead->tytulPL=attributes.at(0).value().toString();
                           nowRead->tytulEN=attributes.at(1).value().toString();
                       }
               }
               else if(name==QString("data")){
                   if(nowRead!=NULL)
                       if(attributes.length()==3){
                           nowRead->dlugosc=attributes.at(0).value().toInt();
                           nowRead->plyta=attributes.at(1).value().toInt();
                           nowRead->koment=attributes.at(2).value().toString();
                       }
               }
               else {}
           }
           else if(type==QXmlStreamReader::TokenType::DTD){
               QStringRef dtdName=reader.dtdName();
               if(dtdName.toString()!=QString("pbdb")) return ;

           }
           else{
               QString type2=reader.text().toString();

               }
           if(reader.hasError()){
               QString typr=reader.errorString();

           }

       }
       file.close();

}

void MainWindow::writeFilm(qFilm *film, QXmlStreamWriter *writer){
    writer->writeStartElement(QString("film"));
    writer->writeStartElement(QString("titles"));
    writer->writeAttribute(QString("pl"),film->tytulPL);
    writer->writeAttribute(QString("eng"),film->tytulEN);
    writer->writeEndElement();
    writer->writeStartElement(QString("data"));
    writer->writeAttribute(QString("length"),QString().setNum(film->dlugosc));
    writer->writeAttribute(QString("disc_No"),QString().setNum(film->plyta));
    writer->writeAttribute(QString("com"),film->koment);
    writer->writeEndElement();
    writer->writeEndElement();
}


void MainWindow::on_actionDodaj_Nowy_Film_triggered()
{
    Dialog1 *u=new Dialog1;
    u->setAttribute(Qt::WA_DeleteOnClose);
    connect(u,SIGNAL(accepted(qFilm*)),this,SLOT(newFilmAdded(qFilm*)));
    u->show();
}

void MainWindow::newFilmAdded(qFilm *film){
    if (film!=NULL){
        elem.append(film);
        len.clear(); disc.clear();
    }
    setLicznik(elem.length());
    ui->comboBox->setCurrentIndex(0);
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    FilmListItem *clicked=dynamic_cast<FilmListItem*>(item);
    if(clicked!=NULL){
        if(clicked->film!=NULL){
            qFilm *f=clicked->film;
            QString opis="Tytuł polski:\n"+f->tytulPL+"\n\nTytuł oryginału:\n"+f->tytulEN+
                    "\n\nNr płyty: "+QString().setNum(f->plyta)+"     Długość: "+
                    QString().setNum(f->dlugosc)+"\n\nKomentarz:\n"+f->koment;
            Dialog2 *u=new Dialog2(opis,f->tytulPL,f);
            u->setAttribute(Qt::WA_DeleteOnClose);
            connect(u,SIGNAL(removeFilm(qFilm*)),this,SLOT(filmDeleted(qFilm*)));
            connect(u,SIGNAL(edited(qFilm*)),this,SLOT(filmChanged(qFilm*)));
            u->show();
            //item->setText(f->tytulPL);
        }
    }

}

void MainWindow::filmDeleted(qFilm *film){
    elem.removeOne(film);
    setLicznik(elem.length());
    for(int i=0;i<ui->listWidget->count();++i){
        FilmListItem *clicked=dynamic_cast<FilmListItem*>(ui->listWidget->item(i));
        if(clicked!=NULL){
            if(clicked->film==film){
                QListWidgetItem *it=ui->listWidget->takeItem(i);
                delete it;
                emit ui->comboBox->activated(ui->comboBox->currentIndex());
            }
        }
    }
}

void MainWindow::filmChanged(qFilm *film){
    for(int i=0;i<ui->listWidget->count();++i){
        FilmListItem *clicked=dynamic_cast<FilmListItem*>(ui->listWidget->item(i));
        if(clicked!=NULL){
            if(clicked->film==film){
                clicked->setText(film->tytulPL);
            }
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->listWidget->clear();

    QList<qFilm *>search=QList<qFilm*>();
    if(ui->comboBox->currentIndex()==0){
        if(ui->lineEdit->text().length()>=2)
            for(int i=0;i<elem.length();++i){
                if(elem.at(i)->tytulPL.contains(ui->lineEdit->text(),Qt::CaseInsensitive) || elem.at(i)->tytulEN.contains(ui->lineEdit->text(),Qt::CaseInsensitive))
                    search.append(elem.at(i));
            }
        else
            search=elem;
    }
    else if(ui->comboBox->currentIndex()==1){
        bool ok=false;
        int discNo=ui->lineEdit->text().toInt(&ok);
        if(ok){
            search=disc.values(discNo);
        }
    }
    else{
        bool ok=false;
        int l=ui->lineEdit->text().toInt(&ok);
        if(ok){
            if(ui->radioButton1->isChecked()){
                for(QMap<int,qFilm*>::iterator i=len.upperBound(l); i!=len.end();++i){
                    search.append(i.value());
                }
            }
            else{
                for(QMap<int,qFilm*>::iterator i=len.begin(); i!=len.lowerBound(l);++i){
                    search.append(i.value());
                }
            }

        }
    }
    for(int i=0;i<search.length();++i){
        FilmListItem *newF= new FilmListItem(search.at(i)->tytulPL);
        newF->film=search.at(i);
        ui->listWidget->addItem(newF);
    }
}

void MainWindow::on_comboBox_activated(int index)
{
    if(index==2){
        ui->radioButton1->setEnabled(true);
        ui->radioButton2->setEnabled(true);
        len.clear();
        for(int i=0;i<elem.length();++i){
            len.insertMulti(elem.at(i)->dlugosc,elem.at(i));
        }
    }
    else if(index==1){
        ui->radioButton1->setEnabled(false);
        ui->radioButton2->setEnabled(false);
        disc.clear();
        for(int i=0;i<elem.length();++i){
            disc.insertMulti(elem.at(i)->plyta,elem.at(i));
        }
    }
    else {
        ui->radioButton1->setEnabled(false);
        ui->radioButton2->setEnabled(false);
    }
}
void MainWindow::setLicznik(int liczba){
    ui->label_3->setText("Filmów w bazie: "+QString::number(liczba));
}
void MainWindow::reset(){
    ui->listWidget->clear();
}
