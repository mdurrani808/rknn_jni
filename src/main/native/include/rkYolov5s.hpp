#ifndef RKYOLOV5S_H
#define RKYOLOV5S_H

#include "rknn_api.h"
#include "postprocess.h"

#include "opencv2/core/core.hpp"

static void dump_tensor_attr(rknn_tensor_attr *attr);
static unsigned char *load_data(FILE *fp, size_t ofst, size_t sz);
static unsigned char *load_model(const char *filename, int *model_size);
static int saveFloat(const char *file_name, float *output, int element_size);

class rkYolov5s
{
private:
    int ret;
    std::mutex mtx;
    std::string model_path;
    unsigned char *model_data;
    int numClasses;

    rknn_context ctx;
    rknn_input_output_num io_num;
    rknn_tensor_attr *input_attrs;
    rknn_tensor_attr *output_attrs;
    rknn_input inputs[1];

    int channel, width, height;
    int img_width, img_height;

    // float nms_threshold, box_conf_threshold;

public:
    rkYolov5s(const std::string &model_path, int numClasses);
    int init(rknn_context *ctx_in, bool isChild);
    rknn_context *get_pctx();

    /**
     * Run forward inference only, returning resulting detections
    */
    int inferOnly(cv::Mat &orig_img, detect_result_group_t *outReults, DetectionFilterParams params);

    ~rkYolov5s();
};

#endif