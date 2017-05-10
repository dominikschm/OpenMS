// --------------------------------------------------------------------------
//                   OpenMS -- Open-Source Mass Spectrometry
// --------------------------------------------------------------------------
// Copyright The OpenMS Team -- Eberhard Karls University Tuebingen,
// ETH Zurich, and Freie Universitaet Berlin 2002-2017.
//
// This software is released under a three-clause BSD license:
//  * Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//  * Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//  * Neither the name of any author or any participating institution
//    may be used to endorse or promote products derived from this software
//    without specific prior written permission.
// For a full list of authors, refer to the file AUTHORS.
// --------------------------------------------------------------------------
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL ANY OF THE AUTHORS OR THE CONTRIBUTING
// INSTITUTIONS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
// ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// --------------------------------------------------------------------------
// $Maintainer: Eugen Netz $
// $Authors: Eugen Netz $
// --------------------------------------------------------------------------

#include <OpenMS/ANALYSIS/XLMS/XQuestXML.h>
#include <OpenMS/FORMAT/Base64.h>
#include <fstream>

using namespace std;

namespace OpenMS
{

// Write xQuest.xml output
  void  XQuestXML::writeXQuestXML(String out_file, String base_name, const std::vector< PeptideIdentification >& peptide_ids, const std::vector< std::vector< CrossLinkSpectrumMatch > >& all_top_csms, const PeakMap& spectra,
                                                String precursor_mass_tolerance_unit, String fragment_mass_tolerance_unit, double precursor_mass_tolerance, double fragment_mass_tolerance, double fragment_mass_tolerance_xlinks, String cross_link_name,
                                                double cross_link_mass_light, DoubleList cross_link_mass_mono_link, String in_fasta, String in_decoy_fasta, StringList cross_link_residue1, StringList cross_link_residue2, double cross_link_mass_iso_shift, String enzyme_name, Size missed_cleavages)
  {
    String spec_xml_name = base_name + "_matched";

    cout << "Writing xquest.xml to " << out_file << endl;
    ofstream xml_file;
    xml_file.open(out_file.c_str(), ios::trunc);
    // XML Header
    xml_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    xml_file << "<?xml-stylesheet type=\"text/xsl\" href=\"\"?>" << endl;

    // TODO!!! write actual experiment data
    // original date/time format: Fri Dec 18 12:28:23 2015
    DateTime time= DateTime::now();
    String timestring = time.getDate() + " " + time.getTime();

//    String precursor_mass_tolerance_unit = getStringOption_("precursor:mass_tolerance_unit");
//    String fragment_mass_tolerance_unit = getStringOption_("fragment:mass_tolerance_unit");
//    double precursor_mass_tolerance = getDoubleOption_("precursor:mass_tolerance");
//    double fragment_mass_tolerance = getDoubleOption_("fragment:mass_tolerance");
//    double fragment_mass_tolerance_xlinks = getDoubleOption_("fragment:mass_tolerance_xlinks");

//    String cross_link_name = getStringOption_("cross_linker:name");
//    double cross_link_mass_light = getDoubleOption_("cross_linker:mass_light");
//    DoubleList cross_link_mass_mono_link = getDoubleList_("cross_linker:mass_mono_link");
    String mono_masses;
    if (cross_link_mass_mono_link.size() > 1)
    {
      for (Size k = 0; k < cross_link_mass_mono_link.size()-1; ++k)
      {
        mono_masses += String(cross_link_mass_mono_link[k]) + ", ";
      }
      mono_masses += cross_link_mass_mono_link[cross_link_mass_mono_link.size()-1];
    }

//    const string in_fasta(getStringOption_("database"));
//    const string in_decoy_fasta(getStringOption_("decoy_database"));
//    StringList cross_link_residue1 = getStringList_("cross_linker:residue1");
//    StringList cross_link_residue2 = getStringList_("cross_linker:residue2");
    String aarequired1, aarequired2;
    for (Size k= 0; k < cross_link_residue1.size()-1; ++k)
    {
      aarequired1 += cross_link_residue1[k] + ",";
    }
    aarequired1 += cross_link_residue1[cross_link_residue1.size()-1];
    for (Size k= 0; k < cross_link_residue2.size()-1; ++k)
    {
      aarequired2 += cross_link_residue2[k] + ",";
    }
    aarequired2 += cross_link_residue2[cross_link_residue2.size()-1];

//    double cross_link_mass_iso_shift = 0;
//    // This parameter is only available for the algorithm for labeled linkers
//    try
//    {
//      cross_link_mass_iso_shift = getDoubleOption_("cross_linker:mass_iso_shift");
//    }
//    catch (...)
//    {
//    }


//    String enzyme_name = getStringOption_("peptide:enzyme");
//    Size missed_cleavages = getIntOption_("peptide:missed_cleavages");

    xml_file << "<xquest_results xquest_version=\"OpenProXL 1.0\" date=\"" << timestring <<
             "\" author=\"Eugen Netz, Timo Sachsenberg\" tolerancemeasure_ms1=\"" << precursor_mass_tolerance_unit  <<
             "\" tolerancemeasure_ms2=\"" << fragment_mass_tolerance_unit << "\" ms1tolerance=\"" << precursor_mass_tolerance <<
             "\" ms2tolerance=\"" << fragment_mass_tolerance << "\" xlink_ms2tolerance=\"" << fragment_mass_tolerance_xlinks <<
             "\" crosslinkername=\"" << cross_link_name << "\" xlinkermw=\"" << cross_link_mass_light <<
             "\" monolinkmw=\"" << mono_masses << "\" database=\"" << in_fasta << "\" database_dc=\"" << in_decoy_fasta <<
             "\" xlinktypes=\"1111\" AArequired1=\"" << aarequired1 << "\" AArequired2=\"" << aarequired2 <<  "\" cp_isotopediff=\"" << cross_link_mass_iso_shift <<
             "\" enzyme_name=\"" << enzyme_name << "\" outputpath=\"" << spec_xml_name <<
             "\" Iontag_charges_for_index=\"1\" missed_cleavages=\"" << missed_cleavages <<
             "\" ntermxlinkable=\"0\" CID_match2ndisotope=\"1" <<
             "\" variable_mod=\"TODO\" nocutatxlink=\"1\" xcorrdelay=\"5\" >" << endl;



    for (vector< vector< CrossLinkSpectrumMatch > >::const_iterator top_csms_spectrum = all_top_csms.begin(); top_csms_spectrum != all_top_csms.end(); ++top_csms_spectrum)
    {
      vector< CrossLinkSpectrumMatch > top_vector = (*top_csms_spectrum);

      if (top_vector.empty())
      {
        continue;
      }
      // Spectrum Data, for each spectrum
      Size scan_index_light = top_vector[0].scan_index_light;
      Size scan_index_heavy = scan_index_light;
      if (cross_link_mass_iso_shift > 0)
      {
        scan_index_heavy = top_vector[0].scan_index_heavy;
      }
      const PeakSpectrum& spectrum_light = spectra[scan_index_light];
      double precursor_charge = spectrum_light.getPrecursors()[0].getCharge();

      double precursor_mz = spectrum_light.getPrecursors()[0].getMZ();
      double precursor_rt = spectrum_light.getRT();
      double precursor_mass = precursor_mz * static_cast<double>(precursor_charge) - static_cast<double>(precursor_charge) * Constants::PROTON_MASS_U;

      double precursor_mz_heavy = spectra[scan_index_heavy].getPrecursors()[0].getMZ();
      double precursor_rt_heavy = spectra[scan_index_heavy].getRT();

      // print information about new peak to file (starts with <spectrum_search..., ends with </spectrum_search>
      String spectrum_light_name = base_name + ".light." + scan_index_light;
      String spectrum_heavy_name = base_name + ".heavy." + scan_index_heavy;

      String spectrum_name = spectrum_light_name + String("_") + spectrum_heavy_name;
      String rt_scans = String(precursor_rt) + ":" + String(precursor_rt_heavy);
      String mz_scans = String(precursor_mz) + ":" + String(precursor_mz_heavy);

      // Mean ion intensity (light spectrum, TODO add heavy spectrum?)
      double mean_intensity= 0;
      if (cross_link_mass_iso_shift > 0)
      {
        for (SignedSize j = 0; j < static_cast<SignedSize>(spectrum_light.size()); ++j) mean_intensity += spectrum_light[j].getIntensity();
        for (SignedSize j = 0; j < static_cast<SignedSize>(spectra[scan_index_heavy].size()); ++j) mean_intensity += spectra[scan_index_heavy][j].getIntensity();
        mean_intensity = mean_intensity / (spectrum_light.size() + spectra[scan_index_heavy].size());
      }
      else
      {
        for (SignedSize j = 0; j < static_cast<SignedSize>(spectrum_light.size()); ++j) mean_intensity += spectrum_light[j].getIntensity();
        mean_intensity = mean_intensity / spectrum_light.size();
      }

      xml_file << "<spectrum_search spectrum=\"" << spectrum_name << "\" mean_ionintensity=\"" << mean_intensity << "\" ionintensity_stdev=\"" << "TODO" << "\" addedMass=\"" << "TODO" << "\" iontag_ncandidates=\"" << "TODO"
          << "\"  apriori_pmatch_common=\"" << "TODO" << "\" apriori_pmatch_xlink=\"" << "TODO" << "\" ncommonions=\"" << "TODO" << "\" nxlinkions=\"" << "TODO" << "\" mz_precursor=\"" << precursor_mz
          << "\" scantype=\"" << "light_heavy" << "\" charge_precursor=\"" << precursor_charge << "\" Mr_precursor=\"" << precursor_mass <<  "\" rtsecscans=\"" << rt_scans << "\" mzscans=\"" << mz_scans << "\" >" << endl;


      for (vector< CrossLinkSpectrumMatch>::const_iterator top_csm = top_csms_spectrum->begin(); top_csm != top_csms_spectrum->end(); ++top_csm)
      {
        String xltype = "monolink";
        String structure = top_csm->cross_link.alpha.toUnmodifiedString();
        String letter_first = structure.substr(top_csm->cross_link.cross_link_position.first, 1);


         // TODO track or otherwise find out, which kind of mono-link it was (if there are several possibilities for the weigths)
        double weight = top_csm->cross_link.alpha.getMonoWeight() + top_csm->cross_link.cross_linker_mass;
//          bool is_monolink = (top_csm->cross_link.cross_link_position.second == -1);
        int alpha_pos = top_csm->cross_link.cross_link_position.first + 1;
        int beta_pos = top_csm->cross_link.cross_link_position.second + 1;

        String topology = String("a") + alpha_pos;
        String id = structure + String("-") + letter_first + alpha_pos + String("-") + static_cast<int>(top_csm->cross_link.cross_linker_mass);

        if (top_csm->cross_link.getType() == ProteinProteinCrossLink::CROSS)
        {
          xltype = "xlink";
          structure += "-" + top_csm->cross_link.beta.toUnmodifiedString();
          topology += String("-b") + beta_pos;
          weight += top_csm->cross_link.beta.getMonoWeight();
          id = structure + "-" + topology;
        }
        else if (top_csm->cross_link.getType() == ProteinProteinCrossLink::LOOP)
        {
          xltype = "intralink";
          topology += String("-b") + beta_pos;
          String letter_second = structure.substr(top_csm->cross_link.cross_link_position.second, 1);
          id = structure + String("-") + letter_first + alpha_pos + String("-") + letter_second + beta_pos;
        }

         // Error calculation
        double cl_mz = (weight + (static_cast<double>(precursor_charge) * Constants::PROTON_MASS_U)) / static_cast<double>(precursor_charge);
        double error = precursor_mz - cl_mz;
        double rel_error = (error / cl_mz) / 1e-6;

        PeptideIdentification pep_id = peptide_ids[top_csm->peptide_id_index];
        vector< PeptideHit > pep_hits = pep_id.getHits();

        String prot_alpha = pep_hits[0].getPeptideEvidences()[0].getProteinAccession();
        if (pep_hits[0].getPeptideEvidences().size() > 1)
        {
          for (Size i = 1; i < pep_hits[0].getPeptideEvidences().size(); ++i)
          {
            prot_alpha = prot_alpha + "," + pep_hits[0].getPeptideEvidences()[i].getProteinAccession();
          }
        }

        String prot_beta = "";

        if (pep_hits.size() > 1)
        {
          prot_beta= pep_hits[1].getPeptideEvidences()[0].getProteinAccession();
          if (pep_hits[1].getPeptideEvidences().size() > 1)
          {
            for (Size i = 1; i < pep_hits[1].getPeptideEvidences().size(); ++i)
            {
              prot_alpha = prot_alpha + "," + pep_hits[1].getPeptideEvidences()[i].getProteinAccession();
            }
          }
        }
        // Hit Data, for each cross-link to Spectrum Hit (e.g. top 5 per spectrum)
        xml_file << "<search_hit search_hit_rank=\"" <<top_csm->rank << "\" id=\"" << id << "\" type=\"" << xltype << "\" structure=\"" << structure << "\" seq1=\"" << top_csm->cross_link.alpha.toUnmodifiedString() << "\" seq2=\"" << top_csm->cross_link.beta.toUnmodifiedString()
              << "\" prot1=\"" << prot_alpha << "\" prot2=\"" << prot_beta << "\" topology=\"" << topology << "\" xlinkposition=\"" << (top_csm->cross_link.cross_link_position.first+1) << "," << (top_csm->cross_link.cross_link_position.second+1)
              << "\" Mr=\"" << weight << "\" mz=\"" << cl_mz << "\" charge=\"" << precursor_charge << "\" xlinkermass=\"" << top_csm->cross_link.cross_linker_mass << "\" measured_mass=\"" << precursor_mass << "\" error=\"" << error
              << "\" error_rel=\"" << rel_error << "\" xlinkions_matched=\"" << (top_csm->matched_xlink_alpha + top_csm->matched_xlink_beta) << "\" backboneions_matched=\"" << (top_csm->matched_common_alpha + top_csm->matched_common_beta)
              << "\" weighted_matchodds_mean=\"" << "TODO" << "\" weighted_matchodds_sum=\"" << "TODO" << "\" match_error_mean=\"" << "TODO" << "\" match_error_stdev=\"" << "TODO" << "\" xcorrx=\"" << top_csm->xcorrx_max << "\" xcorrb=\"" << top_csm->xcorrc_max << "\" match_odds=\"" <<top_csm->match_odds << "\" prescore=\"" << top_csm->pre_score
              << "\" prescore_alpha=\"" << "TODO" << "\" prescore_beta=\"" << "TODO" << "\" match_odds_alphacommon=\"" << "TODO" << "\" match_odds_betacommon=\"" << "TODO" << "\" match_odds_alphaxlink=\"" << "TODO"
              << "\" match_odds_betaxlink=\"" << "TODO" << "\" num_of_matched_ions_alpha=\"" << (top_csm->matched_common_alpha + top_csm->matched_xlink_alpha) << "\" num_of_matched_ions_beta=\"" << (top_csm->matched_common_beta + top_csm->matched_xlink_beta) << "\" num_of_matched_common_ions_alpha=\"" << top_csm->matched_common_alpha
              << "\" num_of_matched_common_ions_beta=\"" << top_csm->matched_common_beta << "\" num_of_matched_xlink_ions_alpha=\"" << top_csm->matched_xlink_alpha << "\" num_of_matched_xlink_ions_beta=\"" << top_csm->matched_xlink_beta << "\" xcorrall=\"" << "TODO" << "\" TIC=\"" << top_csm->percTIC
              << "\" TIC_alpha=\"" << "TODO" << "\" TIC_beta=\"" << "TODO" << "\" wTIC=\"" << top_csm->wTIC << "\" intsum=\"" << top_csm->int_sum * 100 << "\" apriori_match_probs=\"" << "TODO" << "\" apriori_match_probs_log=\"" << "TODO"
              << "\" HyperCommon=\"" << top_csm->HyperCommon << "\" HyperXLink=\"" << top_csm->HyperXlink << "\" HyperAlpha=\"" << top_csm->HyperAlpha << "\" HyperBeta=\"" << top_csm->HyperBeta << "\" HyperBoth=\"" << top_csm->HyperBoth
              << "\" PScoreCommon=\"" << top_csm->PScoreCommon << "\" PScoreXLink=\"" << top_csm->PScoreXlink << "\" PScoreAlpha=\"" << top_csm->PScoreAlpha << "\" PScoreBeta=\"" << top_csm->PScoreBeta << "\" PScoreBoth=\"" << top_csm->PScoreBoth
              << "\" series_score_mean=\"" << "TODO" << "\" annotated_spec=\"" << "" << "\" score=\"" << top_csm->score << "\" >" << endl;
        xml_file << "</search_hit>" << endl;
      }
      // Closing tag for Spectrum
      xml_file << "</spectrum_search>" << endl;
    }

    // Closing tag for results (end of file)
    xml_file << "</xquest_results>" << endl;
    xml_file.close();

    return;
  }

  void XQuestXML::writeXQuestXMLSpec(String out_file, String base_name, const OpenProXLUtils::PreprocessedPairSpectra& preprocessed_pair_spectra, const vector< pair<Size, Size> >& spectrum_pairs, const vector< vector< CrossLinkSpectrumMatch > >& all_top_csms, const PeakMap& spectra)
  {
    //String spec_xml_filename = base_name + "_matched.spec.xml";
    // XML Header
    ofstream spec_xml_file;
    cout << "Writing spec.xml to " << out_file << endl;
    spec_xml_file.open(out_file.c_str(), ios::trunc); // ios::app = append to file, ios::trunc = overwrites file
    // TODO write actual data
    spec_xml_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xquest_spectra compare_peaks_version=\"3.4\" date=\"Tue Nov 24 12:41:18 2015\" author=\"Thomas Walzthoeni,Oliver Rinner\" homepage=\"http://proteomics.ethz.ch\" resultdir=\"aleitner_M1012_004_matched\" deffile=\"xquest.def\" >" << endl;

    for (Size i = 0; i < spectrum_pairs.size(); ++i)
    {
      if (!all_top_csms[i].empty())
      {
        Size scan_index_light = spectrum_pairs[i].first;
        Size scan_index_heavy = spectrum_pairs[i].second;
        // TODO more correct alternative
        String spectrum_light_name = base_name + ".light." + scan_index_light;
        String spectrum_heavy_name = base_name + ".heavy." + scan_index_heavy;
//        String spectrum_light_name = String("spectrumlight") + scan_index_light;
//        String spectrum_heavy_name = String("spectrumheavy") + scan_index_heavy;
        String spectrum_name = spectrum_light_name + String("_") + spectrum_heavy_name;

        // 4 Spectra resulting from a light/heavy spectra pair.  Write for each spectrum, that is written to xquest.xml (should be all considered pairs, or better only those with at least one sensible Hit, meaning a score was computed)
        spec_xml_file << "<spectrum filename=\"" << spectrum_light_name << ".dta" << "\" type=\"light\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(spectra[scan_index_light], String(""));
        spec_xml_file << "</spectrum>" << endl;

        spec_xml_file << "<spectrum filename=\"" << spectrum_heavy_name << ".dta" << "\" type=\"heavy\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(spectra[scan_index_heavy], String(""));
        spec_xml_file << "</spectrum>" << endl;

        String spectrum_common_name = spectrum_name + String("_common.txt");
        spec_xml_file << "<spectrum filename=\"" << spectrum_common_name << "\" type=\"common\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(preprocessed_pair_spectra.spectra_common_peaks[i], spectrum_light_name + ".dta," + spectrum_heavy_name + ".dta");
        spec_xml_file << "</spectrum>" << endl;

        String spectrum_xlink_name = spectrum_name + String("_xlinker.txt");
        spec_xml_file << "<spectrum filename=\"" << spectrum_xlink_name << "\" type=\"xlinker\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(preprocessed_pair_spectra.spectra_xlink_peaks[i], spectrum_light_name + ".dta," + spectrum_heavy_name + ".dta");
        spec_xml_file << "</spectrum>" << endl;
      }
    }

    spec_xml_file << "</xquest_spectra>" << endl;
    spec_xml_file.close();

    return;
  }

  void XQuestXML::writeXQuestXMLSpec(String out_file, String base_name, const vector< vector< CrossLinkSpectrumMatch > >& all_top_csms, const PeakMap& spectra)
  {
    // String spec_xml_filename = base_name + "_matched.spec.xml";
    // XML Header
    ofstream spec_xml_file;
    cout << "Writing spec.xml to " << out_file << endl;
    spec_xml_file.open(out_file.c_str(), ios::trunc); // ios::app = append to file, ios::trunc = overwrites file
    // TODO write actual data
    spec_xml_file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?><xquest_spectra compare_peaks_version=\"3.4\" date=\"Tue Nov 24 12:41:18 2015\" author=\"Thomas Walzthoeni,Oliver Rinner\" homepage=\"http://proteomics.ethz.ch\" resultdir=\"aleitner_M1012_004_matched\" deffile=\"xquest.def\" >" << endl;

    for (Size i = 0; i < spectra.size(); ++i)
    {
      if (!all_top_csms[i].empty())
      {
        String spectrum_light_name = base_name + ".light." + i;
        String spectrum_heavy_name = base_name + ".heavy." + i;

        String spectrum_name = spectrum_light_name + String("_") + spectrum_heavy_name;

        // 4 Spectra resulting from a light/heavy spectra pair.  Write for each spectrum, that is written to xquest.xml (should be all considered pairs, or better only those with at least one sensible Hit, meaning a score was computed)
        spec_xml_file << "<spectrum filename=\"" << spectrum_light_name << ".dta" << "\" type=\"light\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(spectra[i], String(""));
        spec_xml_file << "</spectrum>" << endl;

        spec_xml_file << "<spectrum filename=\"" << spectrum_heavy_name << ".dta" << "\" type=\"heavy\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(spectra[i], String(""));
        spec_xml_file << "</spectrum>" << endl;

        String spectrum_common_name = spectrum_name + String("_common.txt");
        spec_xml_file << "<spectrum filename=\"" << spectrum_common_name << "\" type=\"common\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(spectra[i], spectrum_light_name + ".dta," + spectrum_heavy_name + ".dta");
        spec_xml_file << "</spectrum>" << endl;

        String spectrum_xlink_name = spectrum_name + String("_xlinker.txt");
        spec_xml_file << "<spectrum filename=\"" << spectrum_xlink_name << "\" type=\"xlinker\">" << endl;
        spec_xml_file << getxQuestBase64EncodedSpectrum(spectra[i], spectrum_light_name + ".dta," + spectrum_heavy_name + ".dta");
        spec_xml_file << "</spectrum>" << endl;
      }
    }

    spec_xml_file << "</xquest_spectra>" << endl;
    spec_xml_file.close();

    return;
  }

  String XQuestXML::getxQuestBase64EncodedSpectrum(const PeakSpectrum& spec, String header)
  {
    vector<String> in_strings;
    StringList sl;

    double precursor_mz = spec.getPrecursors()[0].getMZ();
    double precursor_z = spec.getPrecursors()[0].getCharge();

    // header lines
    if (!header.empty()) // common or xlinker spectrum will be reported
    {
      sl.push_back(header + "\n"); // e.g. GUA1372-S14-A-LRRK2_DSS_1A3.03873.03873.3.dta,GUA1372-S14-A-LRRK2_DSS_1A3.03863.03863.3.dta
      sl.push_back(String(precursor_mz) + "\n");
      sl.push_back(String(precursor_z) + "\n");
    }
    else // light or heavy spectrum will be reported
    {
      sl.push_back(String(precursor_mz) + "\t" + String(precursor_z) + "\n");
    }

    // write peaks
    for (Size i = 0; i != spec.size(); ++i)
    {
      String s;
      s += String(spec[i].getMZ()) + "\t";
      s += String(spec[i].getIntensity()) + "\t";

      // add fragment charge if meta value exists (must be present for 'common' and 'xlinker'.
//      if (spec[i].metaValueExists("z"))
//      {
//        s += String(spec[i].getMetaValue("z"));
//      }
      s += "0";

      s += "\n";

      sl.push_back(s);
    }

    String out;
    out.concatenate(sl.begin(), sl.end(), "");
    in_strings.push_back(out);

    String out_encoded;
    Base64().encodeStrings(in_strings, out_encoded, false, false);
    String out_wrapped;
    wrap_(out_encoded, 76, out_wrapped);
    return out_wrapped;
  }

  void XQuestXML::wrap_(const String& input, Size width, String & output)
  {
    Size start = 0;

    while (start + width < input.size())
    {
      output += input.substr(start, width) + "\n";
      start += width;
    }

    if (start < input.size())
    {
      output += input.substr(start, input.size() - start) + "\n";
    }
  }

}
