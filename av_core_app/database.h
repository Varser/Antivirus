#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QMap>

class database
{
private:
    static database _database;
    QMap<QByteArray, QString> _data;
    int _sequence_max_size;
    bool _loaded;

public:
    static void load_database(const QString&);
    static QString check_data(const QByteArray &);
    static bool is_loaded();
    static int get_sequesce_max_size();

private:
    database();
    void load(const QString&);
    database(const database&){}
    database& operator=(const database&);
};

#endif // DATABASE_H
