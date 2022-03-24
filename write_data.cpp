#include <string>
#include <boost/container/map.hpp>
#include <boost/container/string.hpp>
#include <metall/metall.hpp>

template <typename T>
using alloc_type = metall::manager::allocator_type<T>;

int main()
{
    using boost_string = boost::container::string;
    using map_type = boost::container::map<int,
                                           boost_string,
                                           std::less<int>,
                                           alloc_type<std::pair<const int, boost_string>>>;
    std::string dir("/tmp/metalltest");

    metall::manager manager(metall::create_only, dir.c_str());
    map_type *map = manager.construct<map_type>("map")(manager.get_allocator<>());

    map->insert(std::move(std::pair<const int, boost_string>(1, "Hello")));
    map->insert(std::move(std::pair<const int, boost_string>(2, "World")));

    return 0;
}
