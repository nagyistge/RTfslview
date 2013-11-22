#!/usr/bin/env python

import nibabel as nib
from os.path import basename, splitext
from scipy.io import savemat

def load (file = "001.nii.gz"):
	img = nib.load(file)
	fileName = basename(file).split(".")[0]
	savemat(fileName, mdict={'data': img.get_data() })

if __name__ == '__main__':
	data = load()
	