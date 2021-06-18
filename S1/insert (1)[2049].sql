--table Association

INSERT INTO Association(CodeAss, NomAss, NumMembrePresident, DateCreation, Adresse) VALUES('AAEH', 'Association d''’Aide aux Enfants Handicapes', '4', '2001/04/12', '17,Rue n 07, Hai Si Haoues, Aïn Taya');
INSERT INTO Association(CodeAss, NomAss, NumMembrePresident, DateCreation, Adresse) VALUES('AEHG', 'Association El Hachemi Guerouabi', '7' , '23/02/2012', '17, Rue Mohamed Belouizdad');
INSERT INTO Association(CodeAss, NomAss, NumMembrePresident, DateCreation, Adresse) VALUES('AFD', 'Association SOS Femmes en Détresse', '8', '03/08/1999', 'BP 146, Ben Aknoun, Alger Algérie');
INSERT INTO Association(CodeAss, NomAss, NumMembrePresident, DateCreation, Adresse) VALUES('NESKH', 'Nass Elkhir', '3', '24/08/2010', '12, Bouleverd Mohamed V');

--table Wilaya

INSERT INTO Wilaya(CodeWilaya, NomWilaya, Region) VALUES('03', 'Laghouat', 'Sud');
INSERT INTO Wilaya(CodeWilaya, NomWilaya, Region) VALUES('09', 'Blida', 'Centre');
INSERT INTO Wilaya(CodeWilaya, NomWilaya, Region) VALUES('25', 'Constantine', 'Est');
INSERT INTO Wilaya(CodeWilaya, NomWilaya, Region) VALUES('13', 'Tlemcen', 'Ouest');
INSERT INTO Wilaya(CodeWilaya, NomWilaya, Region) VALUES('16', 'Alger', 'Centre');
INSERT INTO Wilaya(CodeWilaya, NomWilaya, Region) VALUES('05', 'Batna', 'Est');


--table Membre

INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('1', 'Atemani Zbdelaziz', 'NESKH', '25', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('2', 'Zerrouki Tarek', 'NESKH', '05', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('3', 'Elias Fellali', 'NESKH', '09', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('4', 'Sari Feirouz', 'AAEH', '16', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('5', 'Djeddi Karim', 'AAEH', '03', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('6', 'Saadi Rabeh', 'AEHG', '13', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('7', 'Allag Nabil', 'AEHG', '05', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('8', 'Rebihi Salima', 'AFD', '16', '');
INSERT INTO Membre(NumeroMembre, NomMembre, CodeAss, CodeWilaya, NumTel) VALUES('9', 'Ghodbane Kawthar', 'AFD', '25', '');


--table TYPE_Manifestation

INSERT INTO TYPE_Manifestation(CodeTypeManif, LibelleTypeManif) VALUES('CONF', 'Conférence');
INSERT INTO TYPE_Manifestation(CodeTypeManif, LibelleTypeManif) VALUES('FEST', 'Festival');
INSERT INTO TYPE_Manifestation(CodeTypeManif, LibelleTypeManif) VALUES('JRE', 'Journées d'’études');
INSERT INTO TYPE_Manifestation(CodeTypeManif, LibelleTypeManif) VALUES('VST', 'Visites');


--table Manifestation

INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('1', 'ENFANCE HORIZON', '07/05/2010', '25', '4', 'CONF');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('2', 'SOLIDAITE', '07/6/2009', '05', '10', 'FEST');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('3', 'JOUNEE DE L'’ENFANT', '7/07/2002', '09', '3', 'JRE');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('4', 'Ecosystème', '07/8/2005', '16', '5', 'CONF');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('5', 'Festival du Tapis', '01/9/2001', '03', '30', 'FEST');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('6', 'JOUNEE DE L'’ORPHELIN', '02/10/2008', '13', '2', 'JRE');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('7', 'VISTES ENFANTS MALADES', '03/11/2010', '05', '1', 'VST');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('8', 'Mouvement Associatif', '04/12/2011', '16', '3', 'CONF');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('9', 'Art Dramatiques', '13/07/2012', '25', '12', 'FEST');
INSERT INTO Manifestation(CodeManif, NomManifestation, DateManif, CodeWilaya, NombrDeJours, CodeTypeManif) VALUES('10','JOUNEE SOS SIDA', '14/05/2004', '25', '2', 'JRE');

--table Participation

INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('1', '6', '4000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('1', '1', '25000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('2', '2', '100000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('3', '3', '50000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('4', '4', '34000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('3', '5', '120000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('4', '7', '2500');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('6', '5', '130000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('6', '8', '13000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('8', '1', '10000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('9', '10', '9000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('5', '7', '5500');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('6', '6', '2600');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('8', '3', '40000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('9', '4', '45000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('7', '8', '65000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('8', '9', '70000');
INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('8', '2', '80000');

INSERT INTO Participation(NumeroMembre, CodeManif, MantantDepenses) VALUES('5', '5', '500000');