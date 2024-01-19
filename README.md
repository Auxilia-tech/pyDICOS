# pyDICOS

[![License](https://img.shields.io/badge/license-MIT-blue)](https://opensource.org/licenses/MIT)

## Motivations

This project was initiated to enable the usage of DICOS data in machine learning workflows. 
PyDICOS is intended to be a simple python wrapper of Stratovan's C++ [DICOS library](https://www.stratovan.com/products/dicos-toolkit).
This project relies on [pybind11](https://github.com/pybind/pybind11) to wrap DICOS user-level API to python.
 It depends on numpy to load data in python and can easily be installed _via_ `pip`.

This project is unrelated to [pydicom](https://github.com/pydicom/pydicom) in its implementation and contributors, 
while being similar in its core spirit (enabling python data manipulations).

## Open Architecture

We firmly believe that by releasing this library, we will encourage and support the [Open Architecture framework](https://www.aci-europe.org/downloads/resources/TSA-230504-7_4.1%20Attachment%201%20OA%20for%20Airport%20Security%20Systems%202nd%20Edition%20%20FINAL.pdf). We welcome all actors of airport security to review and use this library.

## Scope

 - Provide a pythonized API for the DICOS toolkit
   - [x] First release : read/write functions for CT, DX and TDR, user-level API
   - [x] First releases : DICOS protocol, client/server functions
   - [ ] Out of scope for now : AIT2D, AIT3D, QR
   - [ ] Out of scope for now : Module and Tag level APIs
 - Stay up to date with Stratovan latest releases

<div align="center">
<img width="850" src="assets/DICOS.svg">
</div>

## Install

Using [pip](https://pip.pypa.io/en/stable/):
```
pip install pydicos
```

## Contributing

As our resources are limited, we very much value your contributions, be it bug fixes, new core features, or documentation improvements.
For more information, please read our [contribution guide](CONTRIBUTING.md).

### Contributors acknowledgement

Many thanks to our main contributors :

 - [Ahmad Audi](https://github.com/AAUDI) is a freelance developper specialized in C++ and python. He is available for similar work on [upwork](https://www.upwork.com/freelancers/~01a066bd29ed6d1a64). [LinkedIn](https://www.linkedin.com/in/ahmadaudi/)
 - [Louis Combaldieu](https://github.com/lcombaldieu) is the cofounder and CTO of Auxilia. He specializes in deep learning and computer vision. Get in touch with him through our [contact form](https://www.auxilia-tech.com/contact) to learn more about pyDICOS and Auxilia's line of products.

## License

This software is released under the MIT license.

    MIT License
    Copyright (c) 2023 Auxilia
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

### Stratovan inherited disclaimer

    ##############################################################################
    ### Stratovan Corporation Copyright and Disclaimer Notice:
    ###
    ### Copyright (c) 2014 Stratovan Corporation. All Rights Reserved.
    ###
    ### Permission to use, copy, modify, and distribute this software and its
    ### documentation without a signed licensing agreement, is hereby granted,
    ### provided that this copyright notice, this paragraph and the following two
    ### paragraphs appear in all copies, modifications, and distributions.
    ###
    ### IN NO EVENT SHALL STRATOVAN BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT,
    ### SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS,
    ### ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF
    ### STRATOVAN HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    ###
    ### STRATOVAN SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT LIMITED
    ### TO, THE IMPLIED WARRANTIES OF USE AND FITNESS FOR A PARTICULAR PURPOSE. THE
    ### SOFTWARE AND ACCOMPANYING DOCUMENTATION, IF ANY, PROVIDED HEREUNDER IS
    ### PROVIDED "AS IS". STRATOVAN HAS NO OBLIGATION TO PROVIDE MAINTENANCE,
    ### SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS UNLESS DIRECTED BY THE
    ### U.S. GOVERNMENT'S TRANSPORTATION SECURITY ADMINISTRATION (TSA).
    ###
    ##############################################################################