#include <gtest/gtest.h>
#include <vector>


#include "libde265/cabac.h"


class TestCABAC_decoder : public ::testing::Test {
public:
    void SetUp() override 
    {

    }

protected:
    std::vector<uint8_t> data;
};


TEST_F(TestCABAC_decoder, decode)
{
    context_model context_model_table[CONTEXT_MODEL_TABLE_LENGTH]
    initialize_CABAC_models(context_model_table, 0, 0);

    CABAC_decoder decoder;
    init_CABAC_decoder(&decoder, data.data(), data.size());
}
