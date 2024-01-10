# Core module

This directory contains the Core Module which defines
the base functionality of the application. It builds 
into a shared library and will be moved into the `.vega`
directory under `modules/core`.

The default method for recognizing commands is to use 
regex to check. In the future a neural network will 
hopefully be implemented to handle this.