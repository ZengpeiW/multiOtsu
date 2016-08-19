/********************************************************************
 * Otsu multilevel method 
 ********************************************************************/
 #include <iostream>
 #include <vector>
 #include <algorithm>    // std::sort

 const size_t  N = 256;

 unsigned long       histogram[N];
 std::vector<size_t> thresholds;

 //-----------------------------------------------------------------
 void  Otsu_thresholds( unsigned long       min_gray,
                        unsigned long       max_gray,
                        std::vector<size_t> &thresholds,
                        size_t              iter        )
 {
   unsigned long piece = 0;
       for ( size_t i = min_gray; i < max_gray; ++i )
         piece += histogram[i];
   double  max_sigma   = 0.0;
   size_t  thres_index = 0;
       for ( size_t  t = min_gray; t < max_gray; ++t )
       {
         unsigned long  w1  = 0;
         double         mu1 = 0.0;
         double         mu2 = 0.0;
             for ( size_t i = min_gray; i < t; ++i )
             {
               w1  += histogram[i];
               mu1 += i*histogram[i];
             }
             if  ( w1 == 0 ) continue;
             else            mu1 /= w1;
             for ( size_t i = t; i < max_gray; ++i )
             {
               mu2 += i*histogram[i];
             }
         unsigned long long  w2 = piece - w1;
             if  ( w2 == 0 ) continue;
             else            mu2 /= w2;
         double  delta_m = mu1 - mu2;
         double  sigma = w1 * w2 * delta_m * delta_m;
             if ( max_sigma < sigma )
             {
               max_sigma   = sigma;
               thres_index = t;
             }
        } // for ( size_t  t ...
   thresholds.push_back( thres_index );
        if ( --iter > 0 )
        {
          Otsu_thresholds( min_gray,    thres_index, thresholds, iter );
          Otsu_thresholds( thres_index, max_gray,    thresholds, iter );
        }
 }
 //-----------------------------------------------------------------
 std::vector<size_t> Otsu( unsigned long       min_gray,
                           unsigned long       max_gray,
                           std::vector<size_t> &thresholds,
                           size_t              iter = 1     )
 {
   thresholds.clear();
   Otsu_thresholds( min_gray, max_gray, thresholds, iter );
   std::sort( thresholds.begin(), thresholds.end() );
   return thresholds;
 }
 //-----------------------------------------------------------------
 int main()
 {
       for ( size_t i = 0; i < N; ++i )
         histogram[i] = 1;
   std::vector<size_t> thresholds;
   thresholds  = Otsu( 0, N, thresholds, 3 );
    std::cout << "\n ------------\n ";
       for ( const auto &t : thresholds )
         std::cout << t << " ";
   std::cout << "\n ------------\n ";
       for ( size_t i = 0; i < N; ++i )
         std::cout << i << "\t \b\b\b"<< histogram[i] << "\n ";
   //std::cin.get();
   return 0;
 }




















