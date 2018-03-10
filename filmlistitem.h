#ifndef FILMLISTITEM_H
#define FILMLISTITEM_H

#include <QListWidgetItem>

class qFilm;
class FilmListItem : public QListWidgetItem
{



public:
    FilmListItem(QString name);
    FilmListItem();
    virtual ~FilmListItem();
    qFilm *film;
};

#endif // FILMLISTITEM_H
