#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <iostream>
#include <memory>
#include <chrono>
#include <vector>
#include <climits>

int main ()
{
   using namespace boost::interprocess;
   const std::string mappedFileName {"./data/mmap.dat"};

   managed_mapped_file mfile{open_or_create, mappedFileName.c_str(), INT_MAX/1024};  
   //file_mapping fm(FilePath, read_only); 
   //mapped_region region(fm,read_only);



   //Alias an STL-like allocator of ints that allocates ints from the segment
   typedef allocator<char, managed_mapped_file::segment_manager> 
      ShmemAllocator;

   //Alias a vector that uses the previous STL-like allocator
   typedef vector<char, ShmemAllocator> MyVector;

   char initVal[]        = {'T', '[', '2', '3', 'S', 'B', '6', 'A', 's' };
   char initVal1[]        = {'0', '1', '2', '3', '4', '5', '6', 'A', 's' };
   const char *begVal    = initVal;
   const char *endVal    = initVal + sizeof(initVal)/sizeof(initVal[0]);

   //Initialize the STL-like allocator
   const ShmemAllocator alloc_inst (mfile.get_segment_manager());

   //Construct the vector in the shared memory segment with the STL-like allocator 
   //from a range of iterators
   MyVector *myvector = 
      mfile.find_or_construct<MyVector>
         ("MyVector")/*object name*/
         (begVal     /*first ctor parameter*/,
         endVal     /*second ctor parameter*/, 
         alloc_inst /*third ctor parameter*/); 
   std::chrono::microseconds start_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   if (myvector->size() <= sizeof(initVal)/sizeof(initVal[0]))
   {
   for(int i = 0; i < INT_MAX/1024 - 10000; ++i)
   {
       myvector->push_back('a' + i%26);
   }
   }
   std::chrono::microseconds end_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   std::cout << "push first: "<< myvector->size() << " " << end_micro.count() - start_micro.count() << std::endl;
   std::vector<char> stdvector;

   start_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   for(int i = 0; i < INT_MAX/1024 - 10000; ++i)
   {
       stdvector.push_back('a' + i%26);
   }
   end_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   std::cout << "push second: "<< stdvector.size() << " " << end_micro.count() - start_micro.count() << std::endl;
   start_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   for(int i = 0; i < INT_MAX/1024 - 10000; ++i)
   {
        (*myvector)[i] += 1;
   }
   end_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   std::cout << "write first: "<< myvector->size() << " " << end_micro.count() - start_micro.count() << std::endl;
   int kk;
   start_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   for(int i = 0; i < INT_MAX/1024 - 10000; ++i)
   {
       stdvector[i] += 1;
   }
   end_micro = std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::system_clock::now().time_since_epoch());
   std::cout << "write second: "<< stdvector.size() << " " << end_micro.count() - start_micro.count() << std::endl;
   std::chrono::nanoseconds start_nano = std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch());
   for(int i = 0; i < INT_MAX/1024 - 10000; ++i)
   {
        kk = (*myvector)[i];
   }
   std::chrono::nanoseconds end_nano = std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch());
   std::cout << "acceess first: "<< myvector->size() << " " << end_nano.count() - start_nano.count() << std::endl;
   start_nano = std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch());
   for(int i = 0; i < INT_MAX/1024 - 10000; ++i)
   {
       kk = stdvector[i];
   }
   end_nano = std::chrono::duration_cast< std::chrono::nanoseconds >(std::chrono::system_clock::now().time_since_epoch());
   std::cout << "access second: "<< stdvector.size() << " " << end_nano.count() - start_nano.count() << std::endl;


/*


   const std::string mappedFileName2 {"./data/mmap.shared_ptr.dat"};

   managed_mapped_file mfile2{open_or_create, mappedFileName2.c_str(), 1024*1024};  
   //file_mapping fm(FilePath, read_only); 
   //mapped_region region(fm,read_only);



   typedef allocator<std::shared_ptr<char>, managed_mapped_file::segment_manager> 
       SharedAllocator;

   //Alias a vector that uses the previous STL-like allocator
   typedef vector<std::shared_ptr<char>, SharedAllocator> MySharedVector;

   //Initialize the STL-like allocator
   const SharedAllocator alloc_inst2 (mfile2.get_segment_manager());

   //Construct the vector in the shared memory segment with the STL-like allocator 
   //from a range of iterators
   MySharedVector *myvector2 = 
       mfile2.find_or_construct<MySharedVector>
       ("MyVector2")
       (alloc_inst2); 
   std::cout << "myvecto2r->size() "<< myvector2->size() << std::endl;
   if(myvector2->size() == 0)
   {
       for(int i = 0; i < 1024; ++i)
       {
           myvector2->push_back(std::make_shared<char>('a' + i%26));
       }
   }
   std::cout << "myvecto2r->size() "<< myvector2->size() << std::endl;
   for(int i = 0; i < 1024; ++i)
   {
       std::cout << *((*myvector2)[i]) << " ";
   }
*/
   //Use vector as your want
   //std::sort(myvector->rbegin(), myvector->rend());
   // . . .
   //When done, destroy and delete vector from the segment
   //for(auto&& ele : *myvector)
   //{
   //    std::cout << ele << ' ' << std::endl;
   //}

   //mfile.destroy<MyVector>("MyVector");
   return 0;
}
