from distutils.core import setup

setup(
    name='pyDICOS',
    packages=['pyDICOS'],
    version='0.1.0',
    license='MIT',
    description='pyDICOS is a python package for working with DICOS files.',
    author='Louis Combaldieu',
    author_email='louis.combaldieu@auxilia-tech.com',
    url='https://github.com/Auxilia-tech/pydicos',
    download_url='https://github.com/Auxilia-tech/pydicos/',
    keywords=['DICOS', 'Digital', 'Imaging', 'Communications', 'Security'],
    install_requires=[
        'numpy',
    ],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Topic :: Software Development :: Build Tools',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.7',
        'Programming Language :: Python :: 3.8',
        'Programming Language :: Python :: 3.9',
        'Programming Language :: Python :: 3.10',
        'Programming Language :: Python :: 3.11'
    ],
)
