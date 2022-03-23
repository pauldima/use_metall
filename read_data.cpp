#include <iostream>
#include <boost/container/map.hpp>
#include <boost/container/string.hpp>
#include <metall/metall.hpp>

template <typename T>
using alloc_type = metall::manager::allocator_type<T>;

int main()
{
    using string = boost::container::string;
    using map_type = boost::container::map<int,
                                           string,
                                           std::less<int>,
                                           alloc_type<std::pair<const int, string>>>;

    const char *test_dir = "/tmp/metalltest";
    metall::manager manager(metall::open_read_only, test_dir);

    map_type *map;
    std::size_t n;
    std::tie(map, n) = manager.find<map_type>("map");
    std::cout << map->at(1) << " " << map->at(2) << std::endl;

    return 0;
}
