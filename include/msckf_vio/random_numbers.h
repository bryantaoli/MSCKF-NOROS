
#ifndef RANDOM_NUMBERS_RANDOM_NUMBERS_
#define RANDOM_NUMBERS_RANDOM_NUMBERS_

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/normal_distribution.hpp>

namespace random_numbers
{
/** \brief Random number generation (wrapper for boost). An instance of this class
    cannot be used by multiple threads at once (member functions
    are not const). However, the constructor is thread safe and
    different instances can be used safely in any number of
    threads. It is also guaranteed that all created instances will
    have a "random" random seed. */
class RandomNumberGenerator
{
public:
  
  /** \brief Constructor. Always sets a "random" random seed */
  RandomNumberGenerator(void);

  /** \brief Constructor. Allow a seed to be specified for deterministic behaviour */
  RandomNumberGenerator(boost::uint32_t seed);
  
  /** \brief Generate a random real between 0 and 1 */
  double uniform01(void)
  {
    return uni_();
  }
  
  /**
   * @brief Generate a random real within given bounds: [\e lower_bound, \e upper_bound)
   * @param lower_bound The lower bound
   * @param upper_bound The upper bound
   */
  double uniformReal(double lower_bound, double upper_bound)
  {
    return (upper_bound - lower_bound) * uni_() + lower_bound;
  }

  /** \brief Generate a random real using a normal distribution with mean 0 and variance 1 */
  double gaussian01(void)
  {
    return normal_();
  }
  
  /** \brief Generate a random real using a normal distribution with given mean and variance */
  double gaussian(double mean, double stddev)
  {
    return normal_() * stddev + mean;
  }
  
  /** \brief Uniform random unit quaternion sampling. The computed value has the order (x,y,z,w)
   * @param value[4] A four dimensional array in which the computed quaternion will be returned
   */
  void quaternion(double value[4]);
  
  /** \brief Generate an integer uniformly at random within a specified range (inclusive) */
  int uniformInteger(int min, int max)
  {
    boost::uniform_int<> dis(min, max);  
    return dis(generator_);
  }

  /**
   * \brief Allow the randomly generated seed to be saved so that experiments / benchmarks can be recreated in the future
   */
  boost::uint32_t getFirstSeed();
  
private:
  
  boost::mt19937                                                           generator_;
  boost::uniform_real<>                                                    uniDist_; 
  boost::normal_distribution<>                                             normalDist_;
  boost::variate_generator<boost::mt19937&, boost::uniform_real<> >        uni_;  
  boost::variate_generator<boost::mt19937&, boost::normal_distribution<> > normal_;
};

}

#endif
