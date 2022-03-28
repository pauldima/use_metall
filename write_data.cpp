#include <string>
#include <boost/container/map.hpp>
#include <boost/container/string.hpp>
#include <metall/metall.hpp>

template <typename T>
using alloc_type = metall::manager::allocator_type<T>;

int main()
{
    using boost_string = boost::container::basic_string<char, std::char_traits<char>, alloc_type<char>>;
    using my_pair = std::pair<const int, boost_string>;
    using map_type = boost::container::map<int,
                                           boost_string,
                                           std::less<int>,
                                           alloc_type<my_pair>>;
    std::string dir("/tmp/metalltest");

    metall::manager manager(metall::create_only, dir.c_str());
    auto allocator = manager.get_allocator<>();
    map_type *map = manager.construct<map_type>("map")(allocator);
    if(map == nullptr) 
        return 1;

    map->emplace(1, boost_string("Hellooooooooooooooooooooooooooooooooo", allocator));
    map->emplace(2, boost_string("Worldddddddddddddddddddddddddddddddddd", allocator));

    return 0;
}
