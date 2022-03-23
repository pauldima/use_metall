#include <boost/container/map.hpp>
#include <boost/container/string.hpp>
#include <metall/detail/file.hpp>
#include <metall/metall.hpp>


template <typename T>
using alloc_type = metall::manager::allocator_type<T>;

inline bool create_test_dir(const char* dir)
{
    if (!metall::mtlldetail::directory_exist(dir))
        return metall::mtlldetail::create_directory(dir);
    return true;
}

int main()
{
    using string = boost::container::string;
    using map_type = boost::container::map<int,
                                           string,
                                           std::less<int>,
                                           alloc_type<std::pair<const int, string>>>;
    const char *test_dir = "/tmp/metalltest";

    create_test_dir(test_dir);
    metall::manager manager(metall::create_only, test_dir);
    map_type *map = manager.construct<map_type>("map")(manager.get_allocator<>());

    map->insert(std::move(std::pair<const int, string>(1, "Hello")));
    map->insert(std::move(std::pair<const int, string>(2, "World")));

    return 0;
}
