#include "database.h"
#include <QFile>
#include <qDebug>

database database::_database;

database::database() :
    _loaded(false),
    _sequence_max_size(0)
{

}

/*static*/ void database::load_database(const QString& path)
{
    _database.load(path);
}

/*static*/ QString database::check_data(const QByteArray& data)
{
    if (!_database._loaded)
        return QString();

    QString result;
    for (auto iterator = _database._data.cbegin(), cend = _database._data.cend(); iterator != cend; ++iterator)
    {
        if (data.contains(iterator.key()))
        {
            if (!result.isEmpty())
            {
                result.append(", ");
            }
            if (!result.contains(iterator.value()))
                result.append(iterator.value());
        }
    }
    return result;
}

/*static*/ bool database::is_loaded()
{
    if (!_database._loaded)
        qDebug() << "\tError: DataBase is NOT loaded";
    return _database._loaded;
}

/*static*/ int database::get_sequesce_max_size()
{
    if (!_database._loaded)
        return 0;
    return _database._sequence_max_size;
}

void database::load(const QString& path)
{
    _loaded = false;
    _sequence_max_size = 0;
    qDebug() << "\tLoading DataBase from file " << path;
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "\tError opening file " << path;
        return;
    }
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        int delimeter = line.indexOf('.');
        if (delimeter == -1)
            continue;
        QByteArray sequence = line.left(delimeter);
        sequence = sequence.toLower();
        QByteArray guid = line.right(line.size() - delimeter - 1);
        _data.insert(sequence, guid);
        _sequence_max_size = (_sequence_max_size < delimeter) ? delimeter : _sequence_max_size;
        qDebug() << "\tLoaded sequence " << sequence << " with guid " << line.right(line.size() - delimeter - 1);
    }
    if (!_data.empty())
    {
        _loaded = true;
    }
}
