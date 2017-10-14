import os
import sys

from azure.storage.blob import BlockBlobService, ContentSettings

block_blob_service = BlockBlobService(account_name='mirisstorage',
		                                      account_key='KdRI8bpF4kvMvzHzG4yf3jZs+AeKMH1KSQC/efvVPrE7rvXRkVLl5Wo3Ozr9OLJDcUEpfrAQzXZMGOpewe9hCA==')

block_blob_service.create_blob_from_path(
		    'images',
			    sys.argv[1],
				    os.getcwd() + '/image.jpg',
					    content_settings=ContentSettings(content_type='image/jpg')
		)
