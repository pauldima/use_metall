#include <iostream>
#include <tuple>
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
    metall::manager manager(metall::open_only, dir.c_str());

    map_type *map;
    std::tie(map, std::ignore) = manager.find<map_type>("map");
    std::cout << map->at(1) << " " << map->at(2) << std::endl;

    return 0;
}
