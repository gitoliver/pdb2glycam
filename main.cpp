#include "../../gems/gmml/includes/gmml.hpp"

int main()
{
    typedef std::vector<Glycan::Oligosaccharide*> OligosaccharideVector;
    //************************************************//
    // Load Protein PDB file                          //
    //************************************************//

    //std::string working_Directory = Find_Program_Working_Directory();
    std::vector<std::string> amino_libs;
    amino_libs.push_back("../../gems/gmml/dat/CurrentParams/leaprc.ff12SB_2014-04-24/amino12.lib");
    amino_libs.push_back("../../gems/gmml/dat/CurrentParams/leaprc.ff12SB_2014-04-24/aminoct12.lib");
    amino_libs.push_back("../../gems/gmml/dat/CurrentParams/leaprc.ff12SB_2014-04-24/aminont12.lib");

    std::string prep = "../../gems/gmml/dat/CurrentParams/leaprc_GLYCAM_06j-1_2014-03-14/GLYCAM_06j-1.prep";

    Assembly assemblyA ("input.pdb", gmml::InputFileType::PDB);
    assemblyA.BuildStructureByDistance();
    OligosaccharideVector oligos = assemblyA.ExtractSugars(amino_libs);

    gmml::GlycamResidueNamingMap res_map = assemblyA.ExtractResidueGlycamNamingMap(oligos);
    assemblyA.UpdateResidueName2GlycamName(res_map, prep);


    PdbFileSpace::PdbFile *outputPdbFile = assemblyA.BuildPdbFileStructureFromAssembly();
    outputPdbFile->Write("output.pdb");
}

    