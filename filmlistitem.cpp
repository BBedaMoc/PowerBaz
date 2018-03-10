#include "filmlistitem.h"

FilmListItem::FilmListItem() : QListWidgetItem()
{
    film=NULL;
}

FilmListItem::FilmListItem(QString name) : QListWidgetItem(name)
{
    film=NULL;
}

FilmListItem::~FilmListItem(){
    film=NULL;
}
