//
// Created by Gerry on 2021-01-16.
//

#ifndef CPPMC_BLOCKVERTICIES_H
#define CPPMC_BLOCKVERTICIES_H

namespace BG {
    class FaceData;
    enum BlockFace;
    class BlockVerticies {
    public:
        virtual FaceData getFaceData(BlockFace face) = 0;
    };
}
#endif //CPPMC_BLOCKVERTICIES_H
