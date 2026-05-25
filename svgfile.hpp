#include "group.hpp"

class SVGFile : private Group {
   public:
    SVGFile(const char*);
    SVGFile(const SVGFile& o);
    SVGFile& operator=(const SVGFile& o);
    ~SVGFile();

    // TODO: user commands here
    void serialize(std::ostream& os = std::cout, unsigned = 0) const override;
    void deserialize(std::istream& = std::cin) override;
    using Group::addShape;  // making it public

    void print(const unsigned = 0, const unsigned = 0) const override;

   private:
    char* filename;

    void swap(SVGFile& o);
};
