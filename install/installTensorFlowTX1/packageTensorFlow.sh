#!/bin/bash
# NVIDIA Jetson TX1
cd $HOME/tensorflow
bazel-bin/tensorflow/tools/pip_package/build_pip_package /tmp/tensorflow_pkg
mv /tmp/tensorflow_pkg/tensorflow-0.11.0-py2-none-any.whl $HOME/

