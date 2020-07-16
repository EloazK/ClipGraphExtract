#ifndef __GRAPH__EXTRACTOR__
#define __GRAPH__EXTRACTOR__

#include <iostream>

namespace odb {
class dbDatabase;
class dbInst;
}

namespace sta {
class dbSta;
}

namespace ClipGraphExtract {

enum GraphModel {
  Star, Clique, Hybrid
};

enum EdgeWeightModel {
  A, B, C, D, E
};

class ClipGraphExtractor {
  public:
    void setDb(odb::dbDatabase* db);
    void setSta(sta::dbSta* sta);
    void init();
    void clear();
    void extract(int lx, int ly, int ux, int uy);
    void setSaveFileName (const char* fileName);

    void setGraphModel(const char* graphModel);
    void setEdgeWeightModel(const char* edgeWeightModel);

    GraphModel getGraphModel() { return graphModel_; }
    EdgeWeightModel getEdgeWeightModel() { return edgeWeightModel_; }

    ClipGraphExtractor();
    ~ClipGraphExtractor();
  private:
    odb::dbDatabase* db_;
    sta::dbSta* sta_;
    void* rTree_;
    GraphModel graphModel_;
    EdgeWeightModel edgeWeightModel_;
    std::string fileName_;
};

}

#endif
