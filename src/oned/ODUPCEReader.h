#pragma once
/*
* Copyright 2016 ZXing authors
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include "oned/ODUPCEANReader.h"

namespace ZXing {

namespace OneD {

/**
* <p>Implements decoding of the UPC-E format.</p>
* <p><a href="http://www.barcodeisland.com/upce.phtml">This</a> is a great reference for
* UPC-E information.</p>
*
* @author Sean Owen
*/
class UPCEReader : public UPCEANReader
{
protected:
	virtual BarcodeFormat expectedFormat() const override;
	virtual ErrorStatus decodeMiddle(const BitArray& row, int &rowOffset, std::string& resultString) const override;
	virtual	ErrorStatus checkChecksum(const std::string& s) const;
	virtual ErrorStatus decodeEnd(const BitArray& row, int endStart, int& begin, int& end) const;


public:
	/**
	* Expands a UPC-E value back into its full, equivalent UPC-A code value.
	*
	* @param upce UPC-E code as string of digits
	* @return equivalent UPC-A code as string of digits
	*/
	static std::string ConvertUPCEtoUPCA(const std::string& upce);

};

} // OneD
} // ZXing
