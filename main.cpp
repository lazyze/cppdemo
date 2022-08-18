#include <iostream>
#include <string>
#include <vector>

#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/expressions/keyword.hpp>
#include <boost/log/keywords/format.hpp>
#include <boost/log/keywords/target_file_name.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/sources/channel_feature.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/manipulators/dump.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/from_stream.hpp>
#include <fstream>
#include <string>


using namespace std;

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace src = boost::log::sources;
namespace expr = boost::log::expressions;
namespace attrs = boost::log::attributes;
namespace keywords = boost::log::keywords;


std::string glog_format(int id) {
    char szHex[12];
    memset(szHex, 0, sizeof(szHex));
    snprintf(szHex, 12, "0x%08x ", id);
    std::string ans = szHex;
    return ans;
}

std::string glog_dump(const void* data, std::size_t size) {
    if(nullptr == data || 0 == size) {
        return "";
    }
    char szHex[3 * size];
    memset(szHex, 0, sizeof(szHex));
    unsigned char* p = (unsigned char*)data;
    std::size_t idx = 0;
    for (std::size_t i = 0; i < size; i++) {
        idx = i * 3;
        if(i == size - 1) {
            snprintf(&szHex[idx], 3, "%02x", p[i]);
        } else snprintf(&szHex[idx], 4, "%02x ", p[i]);
    }
    std::string ans = szHex;
    return ans;
}

int main() {

    //char* a = "hello";
    //cout << *(std::begin(a));
    int val = 4409441; //00 43 48 61
    int va2 = 4409441; //00 43 48 61
    int va3 = 4409441; //00 43 48 61
    int va4 = 4409441; //00 43 48 61
    int va5 = 4409441; //00 43 48 61
    int va6 = 4409441; //00 43 48 61
    int* vaddr = &val;
    int len = 3;
    cout << "sizeof(int) = " << sizeof(val) << endl;
    cout << "sizeof(int*) = " << sizeof(vaddr) << endl;
    cout << "*vaddr = " << *vaddr << endl;
    cout << "vaddr = " << vaddr << endl;
    cout << "hello world\n";

    vector<int> vec;
    for (int i = 0; i < 10; i ++) {
        vec.push_back(i);
    }

    string str1 = "123456789";
    string str2 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    BOOST_LOG_TRIVIAL(debug) << "test: " << logging::dump(&str1[0], 3);
    BOOST_LOG_TRIVIAL(debug) << "test: " << logging::dump(&str1[0], 3);
    BOOST_LOG_TRIVIAL(debug) << "test: " << logging::dump(&str2[0], 27);

#if 0
    BOOST_LOG_TRIVIAL(trace) << "A trace severity message";
    BOOST_LOG_TRIVIAL(debug) << "A debug severity message";
    BOOST_LOG_TRIVIAL(info) << "An informational severity message";
    BOOST_LOG_TRIVIAL(warning) << "A warning severity message";
    BOOST_LOG_TRIVIAL(error) << "An error severity message";
    BOOST_LOG_TRIVIAL(fatal) << "A fatal severity message";


    BOOST_LOG_TRIVIAL(debug) << logging::dump((void *)vaddr, len);

    BOOST_LOG_TRIVIAL(debug) << boost::format("0x%08x ") % len <<  logging::dump((void *)vaddr, len);

    BOOST_LOG_TRIVIAL(debug) << logging::dump((void *)&vec, 10);

    BOOST_LOG_TRIVIAL(debug) << boost::format("0x%08x ") % 10 <<  logging::dump((void *)&vec, 10);

    cout << "my test log dump       :" << glog_dump(vaddr, len) << endl;

    cout << "my test log format dump:" << glog_format(len) << glog_dump(vaddr, len) << endl;

    cout << "my test log dump       :" << glog_dump(&vec, 10) << endl;

    cout << "my test log format dump:" << glog_format(10) << glog_dump(&vec, 10) << endl;


    //00 00 00 01 00 00 00 02
    //01 00 00 00 02 00 00 00 03 00 00 00 04 00 00 00
    //02 00 00 00 03 00 00 00 00
    //05 00 00 00 06 00 00 00 00

    cout << "************************** begin **************************" << endl;
    BOOST_LOG_TRIVIAL(debug) << "boost:" << logging::dump((void *)&vec, 8);
    BOOST_LOG_TRIVIAL(debug) << "golg :" << glog_dump((void *)&vec, 8);
    //BOOST_LOG_TRIVIAL(debug) << "boost:" << boost::format("0x%08x ") % 8 <<  logging::dump((void *)&vec, 8);
    //BOOST_LOG_TRIVIAL(debug) << "glog :" << "pp" << glog_dump((void *)&vec, 8) << "tt";
    //BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_dump(&vec, 8) << glog_dump(&vec, 8) << "TT";
    //BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_format(8) << glog_dump(&vec, 8);
    BOOST_LOG_TRIVIAL(debug) << "boost:" << boost::format("0x%08x ") % 8 <<  logging::dump((void *)&vec, 8);
    BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_format(8) << glog_dump(&vec, 8);
    //BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_format(8) << glog_dump(&vec, 8);
    //BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_dump(&vec, 8) <<glog_format(8) << glog_format(16);
    //cout << strlen(glog_dump(&vec, 8).c_str()) << endl;
    //cout << glog_dump(&vec, 8).c_str() << endl;
    //cout << glog_format(8) << "endendend" << endl;
    //cout << glog_format(8) <<  glog_dump(&vec, 8).c_str() << endl;
    BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_format(8) << glog_dump(&vec, 8);


    BOOST_LOG_TRIVIAL(debug) << "boost:" << logging::dump((void *)&vec[0], 16);
    BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_dump(&vec[0], 16);
    BOOST_LOG_TRIVIAL(debug) << "boost:" << boost::format("0x%08x ") % 16 <<  logging::dump((void *)&vec[0], 16);
    BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_format(16) << glog_dump(&vec[0], 16);


    BOOST_LOG_TRIVIAL(debug) << "boost:" << logging::dump((void *)&vec[1], 8);
    BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_dump(&vec[1], 8);
    BOOST_LOG_TRIVIAL(debug) << "boost:" << boost::format("0x%08x ") % 8 <<  logging::dump((void *)&vec[1], 8);
    BOOST_LOG_TRIVIAL(debug) << "glog :" << glog_format(8) << glog_dump(&vec[1], 8);


    cout << "************************** end **************************" << endl;

    string a = "hello world";
    BOOST_LOG_TRIVIAL(debug) << a << a << a;
#endif
    return 0;
}