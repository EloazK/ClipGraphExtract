# ClipGraphExtract
- An example repo for adding the tool in DAC 2020 tutorial 9.
- The ClipGraphExtract is an example of using the OpenDB-C++-API and porting the projects to the top-level app.
- The base sources are copied from [OpenROAD](https://github.com/The-OpenROAD-Project/OpenROAD) repo, commit: [7156dc](https://github.com/The-OpenROAD-Project/OpenROAD/commit/7156dc41b0be75e9090b456103a2a1510913a4d2)
- Please read the [doc/OpenRoadArch.md](https://github.com/The-OpenROAD-Project/OpenROAD/blob/master/doc/OpenRoadArch.md) to understand the requirement. The ClipGraphExtract is an  example that follows the OpenRoadArch.md.

# ClipGraphExtract Flow
| <img src="/doc/clique-star.png" width=600px> |
|:--:|
| Clique and star net decomposition example |
- Takes LEF/DEF using OpenDB
- Save all instances' bbox to Boost/RTree structure. 
- Send region query to RTree to get related instances using the clips' coordinates.
- Generate clip graph's clique/star net models as text file (e.g. edges list) for graph neural network models.

# File Structure
-  include/openroad/  
    - public headers location of OpenROAD.

- src/ 
    - OpenROAD source code files. The tools source code should be located in here. 
  
- src/ClipGraphExtractor/src/  
    - source code location of ClipGraphExtractor.
  
- src/ClipGraphExtractor/include/clip_graph_ext/  
    - public headers location of ClipGraphExtractor.
  

# Implementation Details
## OpenDB C++ API
- All the OpenDB reference is in the OpenDB's public header [(OpenDB/include/opendb/db.h)](https://github.com/The-OpenROAD-Project/OpenDB/blob/ebbf56ee8ddb08f9a8da5febafe37691731f2932/include/opendb/db.h). Please check this header file first to understand how the structures are designed.

- Set the OpenDB pointer from Top-level app [(Link)](https://github.com/mgwoo/ClipGraphExtract/blob/ead17cee5b4bde069b64913a9d1d3749cf3d4f92/src/ClipGraphExtract/src/MakeClipGraphExtractor.cpp#L30-L31)

      void 
      initClipGraphExtractor(OpenRoad *openroad) 
      {
        Tcl_Interp* tcl_interp = openroad->tclInterp();
        Clipgraphextractor_Init(tcl_interp);
        sta::evalTclInit(tcl_interp, sta::graph_extractor_tcl_inits);
        openroad->getClipGraphExtractor()->setDb(openroad->getDb());
        openroad->getClipGraphExtractor()->setSta(openroad->getSta());
      }
    
- Push instances' location to RTree using dbInst* [(Link)](https://github.com/mgwoo/ClipGraphExtract/blob/ead17cee5b4bde069b64913a9d1d3749cf3d4f92/src/ClipGraphExtract/src/clipGraphExtractor.cpp#L74-L80)

      dbBlock* block = db_->getChip()->getBlock();
      for( dbInst* inst : block->getInsts() ) {
        dbBox* bBox = inst->getBBox();
        box b (point(bBox->xMin(), bBox->yMin()), 
                point(bBox->xMax(), bBox->yMax()));
        rTree->insert( make_pair(b, inst) );
      }

- Store distinctive instances into hash_set (e.g. std::set<dbInst*>) [(Link)](https://github.com/mgwoo/ClipGraphExtract/blob/ead17cee5b4bde069b64913a9d1d3749cf3d4f92/src/ClipGraphExtract/src/clipGraphExtractor.cpp#L110-L119)

      set<odb::dbInst*> instSet;
      for(value& val : foundInsts) {
        odb::dbInst* inst = val.second;
    
        int lx = 0, ly = 0;
        inst->getLocation(lx, ly);
        instSet.insert( inst ); 
      }


## Adding a Tool




# License
- BSD-3-Clause license. 
- Code found under the sub directory (e.g., src/OpenSTA) have individual copyright and license declarations at each folder.
