
 
#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageSeriesWriter.h"
#include "itkNumericSeriesFileNames.h"
#include "header.h"
 

void ImageReadImageSeriesWrite(char * input, char * output, char * extension){
  if (argc < 4){
    std::cerr
      << "Usage: ImageReadImageSeriesWrite inputFile outputPrefix outputExtension"
      << std::endl;
  }
  using ImageType = itk::Image<unsigned char, 3>;
  using ReaderType = itk::ImageFileReader<ImageType>;
  
  ReaderType::Pointer reader = ReaderType::New();
  reader->SetFileName(input]);
  
  using Image2DType = itk::Image<unsigned char, 2>;
  using WriterType = itk::ImageSeriesWriter<ImageType, Image2DType>;
  
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput(reader->GetOutput());
  
  using NameGeneratorType = itk::NumericSeriesFileNames;
  NameGeneratorType::Pointer nameGenerator = NameGeneratorType::New();

  std::string format = output;
  format += "%03d.";
  format += extension; 
  nameGenerator->SetSeriesFormat(format.c_str());
  
  try{
    reader->Update();
  }
  catch (const itk::ExceptionObject & excp){
    std::cerr << "Exception thrown while reading the image" << std::endl;
    std::cerr << excp << std::endl;
  }
   
  ImageType::ConstPointer inputImage = reader->GetOutput();
  ImageType::RegionType region = inputImage->GetLargestPossibleRegion();
  ImageType::IndexType start = region.GetIndex();
  ImageType::SizeType size = region.GetSize();
  
  const unsigned int firstSlice = start[2];
  const unsigned int lastSlice = start[2] + size[2] - 1;
 
  nameGenerator->SetStartIndex(firstSlice);
  nameGenerator->SetEndIndex(lastSlice);
  nameGenerator->SetIncrementIndex(1);
  
  writer->SetFileNames(nameGenerator->GetFileNames());
 
  try{
    writer->Update();
  }
  catch (const itk::ExceptionObject & excp){
    std::cerr << "Exception thrown while reading the image" << std::endl;
    std::cerr << excp << std::endl;
  } 
}
