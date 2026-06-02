


    // !!! This file is generated using emlearn !!!

    #include <stdint.h>
    

static inline int32_t boxing_model_tree_0(const int16_t *features, int32_t features_length) {
          if (features[5] < -160) {
              if (features[10] < 1124) {
                  if (features[17] < 2076) {
                      return 2;
                  } else {
                      return 0;
                  }
              } else {
                  if (features[11] < 2404) {
                      return 2;
                  } else {
                      if (features[11] < 2410) {
                          return 0;
                      } else {
                          return 2;
                      }
                  }
              }
          } else {
              if (features[8] < -1001) {
                  return 1;
              } else {
                  if (features[13] < -1228) {
                      return 0;
                  } else {
                      return 2;
                  }
              }
          }
        }
        

static inline int32_t boxing_model_tree_1(const int16_t *features, int32_t features_length) {
          if (features[5] < -186) {
              if (features[14] < 2236) {
                  if (features[13] < -480) {
                      if (features[3] < -2202) {
                          if (features[2] < 4882) {
                              return 0;
                          } else {
                              return 2;
                          }
                      } else {
                          if (features[15] < 3353) {
                              return 0;
                          } else {
                              return 2;
                          }
                      }
                  } else {
                      return 2;
                  }
              } else {
                  return 2;
              }
          } else {
              return 1;
          }
        }
        

static inline int32_t boxing_model_tree_2(const int16_t *features, int32_t features_length) {
          if (features[5] < -175) {
              if (features[13] < -745) {
                  if (features[7] < 1367) {
                      if (features[12] < 4146) {
                          return 0;
                      } else {
                          if (features[5] < -2409) {
                              return 0;
                          } else {
                              return 2;
                          }
                      }
                  } else {
                      return 2;
                  }
              } else {
                  if (features[8] < -1138) {
                      if (features[10] < 523) {
                          if (features[14] < 425) {
                              return 2;
                          } else {
                              return 0;
                          }
                      } else {
                          return 2;
                      }
                  } else {
                      return 0;
                  }
              }
          } else {
              return 1;
          }
        }
        

static inline int32_t boxing_model_tree_3(const int16_t *features, int32_t features_length) {
          if (features[7] < 1347) {
              if (features[3] < -3064) {
                  if (features[3] < -3710) {
                      return 0;
                  } else {
                      if (features[12] < 2722) {
                          if (features[2] < 4298) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          return 2;
                      }
                  }
              } else {
                  if (features[10] < -18) {
                      if (features[7] < 757) {
                          if (features[18] < 1221) {
                              return 2;
                          } else {
                              return 0;
                          }
                      } else {
                          return 1;
                      }
                  } else {
                      if (features[18] < 3663) {
                          if (features[17] < 6259) {
                              return 2;
                          } else {
                              return 0;
                          }
                      } else {
                          return 2;
                      }
                  }
              }
          } else {
              if (features[10] < 93) {
                  if (features[10] < -991) {
                      if (features[17] < 5054) {
                          return 0;
                      } else {
                          return 1;
                      }
                  } else {
                      return 1;
                  }
              } else {
                  return 2;
              }
          }
        }
        

static inline int32_t boxing_model_tree_4(const int16_t *features, int32_t features_length) {
          if (features[7] < 1179) {
              if (features[14] < 1842) {
                  if (features[9] < 1034) {
                      if (features[15] < 1939) {
                          return 2;
                      } else {
                          return 1;
                      }
                  } else {
                      if (features[18] < 2977) {
                          if (features[3] < -2569) {
                              return 0;
                          } else {
                              return 1;
                          }
                      } else {
                          if (features[4] < 1362) {
                              return 2;
                          } else {
                              return 0;
                          }
                      }
                  }
              } else {
                  if (features[3] < -3952) {
                      return 0;
                  } else {
                      if (features[9] < 1297) {
                          return 0;
                      } else {
                          return 2;
                      }
                  }
              }
          } else {
              if (features[5] < -325) {
                  if (features[12] < 1925) {
                      return 0;
                  } else {
                      return 2;
                  }
              } else {
                  return 1;
              }
          }
        }
        

int32_t boxing_model_predict(const int16_t *features, int32_t features_length) {

        int32_t votes[3] = {0,};
        int32_t _class = -1;

        _class = boxing_model_tree_0(features, features_length); votes[_class] += 1;
    _class = boxing_model_tree_1(features, features_length); votes[_class] += 1;
    _class = boxing_model_tree_2(features, features_length); votes[_class] += 1;
    _class = boxing_model_tree_3(features, features_length); votes[_class] += 1;
    _class = boxing_model_tree_4(features, features_length); votes[_class] += 1;
    
        int32_t most_voted_class = -1;
        int32_t most_voted_votes = 0;
        for (int32_t i=0; i<3; i++) {

            if (votes[i] > most_voted_votes) {
                most_voted_class = i;
                most_voted_votes = votes[i];
            }
        }
        return most_voted_class;
    }
    

int boxing_model_predict_proba(const int16_t *features, int32_t features_length, float *out, int out_length) {

        int32_t _class = -1;

        for (int i=0; i<out_length; i++) {
            out[i] = 0.0f;
        }

        _class = boxing_model_tree_0(features, features_length); out[_class] += 1.0f;
    _class = boxing_model_tree_1(features, features_length); out[_class] += 1.0f;
    _class = boxing_model_tree_2(features, features_length); out[_class] += 1.0f;
    _class = boxing_model_tree_3(features, features_length); out[_class] += 1.0f;
    _class = boxing_model_tree_4(features, features_length); out[_class] += 1.0f;
    
        // compute mean
        for (int i=0; i<out_length; i++) {
            out[i] = out[i] / 5;
        }
        return 0;
    }
    