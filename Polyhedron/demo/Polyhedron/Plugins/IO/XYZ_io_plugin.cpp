#include "Scene_points_with_normal_item.h"
#include "Kernel_type.h"

#include <QMainWindow>
#include <CGAL/Three/Polyhedron_demo_io_plugin_interface.h>
#include <fstream>
#include <QMessageBox>
#include <QMenu>
using namespace CGAL::Three;

class Polyhedron_demo_xyz_plugin :
  public QObject,
  public Polyhedron_demo_io_plugin_interface
{
  Q_OBJECT
  Q_INTERFACES(CGAL::Three::Polyhedron_demo_io_plugin_interface)
  Q_PLUGIN_METADATA(IID "com.geometryfactory.PolyhedronDemo.IOPluginInterface/1.0")

public:

  QString name() const { return "xyz_plugin"; }
  QString nameFilters() const { return "XYZ as Point Set (*.xyz);;Point Set with Normal (*.pwn)"; }
  bool canLoad() const;
  CGAL::Three::Scene_item* load(QFileInfo fileinfo);

  bool canSave(const CGAL::Three::Scene_item*);
  bool save(const CGAL::Three::Scene_item*, QFileInfo fileinfo);
};

bool Polyhedron_demo_xyz_plugin::canLoad() const {
  return true;
}


CGAL::Three::Scene_item*
Polyhedron_demo_xyz_plugin::load(QFileInfo fileinfo)
{
  // Open file
  std::ifstream in(fileinfo.filePath().toUtf8().data());
  if(!in) {
    std::cerr << "Error! Cannot open file " << fileinfo.filePath().toStdString() << std::endl;
    return NULL;
  }

  // Read .xyz in a point set
  Scene_points_with_normal_item* point_set_item = new Scene_points_with_normal_item;
  point_set_item->setName(fileinfo.completeBaseName());
  if(!point_set_item->read_xyz_point_set(in)) {
    delete point_set_item;
    return NULL;
  }
  return point_set_item;
}

bool Polyhedron_demo_xyz_plugin::canSave(const CGAL::Three::Scene_item* item)
{
  // This plugin supports point sets
  return qobject_cast<const Scene_points_with_normal_item*>(item);
}

bool Polyhedron_demo_xyz_plugin::save(const CGAL::Three::Scene_item* item, QFileInfo fileinfo)
{
  // Check extension (quietly)
  std::string extension = fileinfo.suffix().toUtf8().data();
  if (extension != "xyz" && extension != "XYZ" &&
      extension != "pwn" && extension != "PWN")
    return false;

  // This plugin supports point sets
  const Scene_points_with_normal_item* point_set_item =
    qobject_cast<const Scene_points_with_normal_item*>(item);
  if(!point_set_item)
    return false;

  // Save point set as .xyz
  std::ofstream out(fileinfo.filePath().toUtf8().data());
  out.precision (std::numeric_limits<double>::digits10 + 2);
  return point_set_item->write_xyz_point_set(out);
}

#include "XYZ_io_plugin.moc"
