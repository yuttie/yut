#ifndef WINDOWED_HPP
#define WINDOWED_HPP


#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/sub_range.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/utility.hpp>


namespace yut {


    template <class Range>
    struct windowed_iterator
        : public boost::iterator_facade<
            windowed_iterator<Range>,
            boost::sub_range<Range> const,
            boost::forward_traversal_tag
        >
    {
        windowed_iterator()
            : cur_rng_(), end_it_()
        {}

        windowed_iterator(Range const& r, std::size_t len)
            : cur_rng_(boost::begin(r), boost::next(boost::begin(r), len)),
              end_it_(boost::end(r))
        {}

    private:
        friend class boost::iterator_core_access;

        typedef typename boost::range_iterator<Range>::type rng_iterator;
        typedef boost::sub_range<Range> sub_range;

        sub_range const& dereference() const {
            return cur_rng_;
        }

        bool equal(windowed_iterator const& other) const {
            return this->cur_rng_ == other.cur_rng_;
        }

        void increment() {
            if (cur_rng_.end() == end_it_) {
                cur_rng_ = sub_range();
                end_it_ = rng_iterator();
            }
            else {
                cur_rng_.advance_begin(1);
                cur_rng_.advance_end(1);
            }
        }

    private:
        sub_range cur_rng_;
        rng_iterator end_it_;
    };


    template <class Range>
    struct windowed_range : boost::iterator_range<windowed_iterator<Range> > {
        typedef windowed_iterator<Range> iterator;

    private:
        typedef boost::iterator_range<windowed_iterator<Range> > base;

    public:
        windowed_range(Range& r, std::size_t length)
            : base(iterator(r, length), iterator())
        {}
    };

    struct windowed {
        windowed(std::size_t length)
            : length_(length)
        {}
        std::size_t length_;
    };

    template <class ForwardRng>
    inline windowed_range<ForwardRng>
    operator|(ForwardRng& r, windowed const& f) {
        return windowed_range<ForwardRng>(r, f.length_);
    }

    template <class ForwardRng>
    inline windowed_range<const ForwardRng>
    operator|(ForwardRng const& r, windowed const& f) {
        return windowed_range<const ForwardRng>(r, f.length_);
    }


}  // namespace yut


#endif  /* WINDOWED_HPP */
