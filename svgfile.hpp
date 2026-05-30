#include "group.hpp"

class SVGFile : private Group {
   public:
    SVGFile(const char*);
    SVGFile(const SVGFile&);
    SVGFile(const SVGFile&, const char*);
    SVGFile& operator=(const SVGFile&);
    ~SVGFile();

    // TODO: user commands here
    void serialize(std::ostream& = std::cout, unsigned = 0) const override;
    void serializeToFile(const char*) const;
    void deserialize(std::istream& = std::cin) override;
    using Group::addShape;
    using Group::translate;  // making it public
    void removeShape(unsigned number);

    void print(const unsigned = 0, const std::vector<unsigned>& = {}) const override;

   private:
    char* filename;

    void swap(SVGFile& o);
};
