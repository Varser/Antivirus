#include "scanner_manager.h"

scanner_manager scanner_manager::_manager;
SCANNER_ID scanner_manager::_id = 0;

scanner_manager::scanner_manager()
{
}

scanner_manager::~scanner_manager()
{
}

scanner_manager::scanner_manager(const scanner_manager&)
{
}

/*static*/ SCANNER_ID scanner_manager::create_scanner(const QString& file)
{
    auto current_id = ++scanner_manager::_id;

    QSharedPointer<scanner> t_scanner(new scanner(file),
        [](scanner* p){p->stop(); p->quit(); p->wait(); delete p;});

    _manager._scanners.insert(current_id, t_scanner);

    t_scanner->start();

    return current_id;
}

/*static*/ SCANNER_ID scanner_manager::create_scanner(const QByteArray& data)
{
    auto current_id = ++scanner_manager::_id;

    QSharedPointer<scanner> t_scanner(new scanner(data),
        [](scanner* p){p->stop(); p->quit(); p->wait(); delete p;});

    _manager._scanners.insert(current_id, t_scanner);

    t_scanner->start();

    return current_id;
}

/*static*/ int scanner_manager::get_percent(SCANNER_ID id)
{
    auto iter = _manager._scanners.find(id);

    if (iter == _manager._scanners.end())
        return 100;

    return iter.value()->get_percent();
}

/*static*/ QString scanner_manager::get_threats(SCANNER_ID id)
{
    auto iter = _manager._scanners.find(id);

    if (iter == _manager._scanners.end())
        return QString();

    return iter.value()->get_threats();
}

/*static*/ void scanner_manager::process_stop(SCANNER_ID id)
{
    auto iter = _manager._scanners.find(id);

    if (iter == _manager._scanners.end())
        return;

    _manager._scanners.erase(iter);
}

/*static*/ void scanner_manager::process_pause(SCANNER_ID id)
{
    auto iter = _manager._scanners.find(id);

    if (iter == _manager._scanners.end())
        return;

    iter.value()->pause(true);
}

/*static*/ void scanner_manager::process_unpause(SCANNER_ID id)
{
    auto iter = _manager._scanners.find(id);

    if (iter == _manager._scanners.end())
        return;

    iter.value()->pause(false);

}
